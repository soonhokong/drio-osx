/* Author: Jichao Sun <jichaos@andrew.cmu.edu> 
 * Copyright 2014 Jichao Sun
 */

%skeleton "lalr1.cc"
%debug
%defines
%define api.namespace {shell}
%define parser_class_name {parser}

%code requires{
    namespace shell{
        class driver;
        class scanner;
    }
}

%lex-param   { class scanner  &scanner  }
%parse-param { class scanner  &scanner  }
 
%lex-param   { class driver  &driver  }
%parse-param { class driver  &driver  }

%code{
    #include <iostream>
    #include <cstdlib>
    #include "driver.h"

   static int yylex(shell::parser::semantic_type *yylval,
                    shell::scanner  &scanner,
                    shell::driver   &driver);
}

%union {
    double num; 
    std::string *var;
}

%start          line

%token          t_real
%token          t_int
%token          GE
%token          LE
%token          GEQ
%token          LEQ
%token          EQ

%token          formula
%token          eval
%token          define

%token          print  
%token          printenv
%token          quit


%token  <num>   number
%token  <var>   variable

%type   <num>   stmt exp term
%type   <var>   assignment
%left           '+' '-'
%left           '*' '/'
%nonassoc       UMINUS

%destructor { if ($$)  { delete ($$); ($$) = nullptr; } } <var>


%%
line        : stmt
            | line stmt
            ;

stmt        : '\n'                  { ; }
            | assignment '\n'       { ; }
            | variable eval         { driver.eval(*$1); }
            | exp '\n'              { driver.print($1); }
            | eq_op '\n'            { ; }
            | quit '\n'             { exit(0); }
            | print exp '\n'        { driver.print($2); }
            | printenv '\n'         { driver.print_env(); }
            ;

eq_op       : exp EQ exp            { $1 == $3 ? std::cout << "true\n" : std::cout <<            "false\n";}
            | exp GE exp            { $1 > $3 ? std::cout << "true\n" : std::cout << "false\n";}
            | exp LE exp            { $1 < $3 ? std::cout << "true\n" : std::cout << "false\n";}
            | exp GEQ exp           { $1 >= $3 ? std::cout << "true\n" : std::cout << "false\n";}
            | exp LEQ exp           { $1 <= $3 ? std::cout << "true\n" : std::cout << "false\n";}

assignment  : variable '=' exp      { driver.update_var(*$1, "real", $3); }
            | t_real variable       { driver.update_var(*$2, "real", 0); } 
            | t_int variable        { driver.update_var(*$2, "int", 0); } 
            | formula variable      { driver.update_form(*$2, 0); } 
            | variable define exp   { driver.update_form(*$1, $3); }
            ;

exp         : term              
            | '-' exp %prec UMINUS  { $$ = -$2; }
            | exp '+' exp           { $$ = $1 + $3; }
            | exp '-' exp           { $$ = $1 - $3; }
            | exp '*' exp           { $$ = $1 * $3; }
            | exp '/' exp           { $$ = $1 / $3; }
            | '(' exp ')'           { $$ = $2; }
            ;

term        : number            
            | variable              { $$ = driver.get_var(*$1); }
%%

// C++ Code:

void 
shell::parser::error( const std::string &err_message )
{
   std::cerr << "Error: " << err_message << "\n"; 
}

#include "scanner.h"

static int yylex( shell::parser::semantic_type *yylval,
                  shell::scanner  &scanner,
                  shell::driver   &driver ){
   return(scanner.yylex(yylval));
}
