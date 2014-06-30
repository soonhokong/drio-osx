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

%start          stmt
%token          t_real
%token          t_int
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
stmt        : '\n'                  { ; }
            | assignment '\n'       { ; }
            | exp '\n'              { driver.print($1); }
            | quit '\n'             { exit(0); }
            | print exp '\n'        { driver.print($2); }
            | printenv '\n'         { driver.print_env(); }
	        | stmt '\n'             { ; }
            | stmt exp '\n'         { driver.print($2); }
            | stmt assignment '\n'  { ; }
            | stmt quit '\n'        { exit(0); }
            | stmt print exp '\n'   { driver.print($3); }
            | stmt printenv '\n'    { driver.print_env(); }
            ;

assignment  : variable '=' exp      { driver.update_var(*$1,"real",$3); }
            | t_real variable       { driver.update_var(*$2,"real",0); } 
            | t_int variable        { driver.update_var(*$2,"int",0); }  
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
