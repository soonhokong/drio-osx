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
    #include <string>
    #include "driver.h"

   static int yylex(shell::parser::semantic_type *yylval,
                    shell::scanner  &scanner,
                    shell::driver   &driver);
}

%union {
    double num; 
    std::string *str;
    bool bval;
}

%start          line

%token          realnum
%token          intnum
%token          GE
%token          LE
%token          GEQ
%token          LEQ
%token          EQ

%token          t_not
%token          t_and
%token          t_or
%token          implies
%token          forall
%token          exists


%token          formula
%token          eval
%token  <str>   define

%token          print  
%token          printenv
%token          quit

%token  <num>   number
%token  <str>   var

%type   <num>   stmt exp term
%type   <str>   assignment 
%type   <bval>  eq_op lgc
%left           '+' '-'
%left           '*' '/'
%nonassoc       UMINUS
%nonassoc       UNOT

%destructor { if ($$)  { delete ($$); ($$) = nullptr; } } <str>


%%
line        : stmt
            | line stmt
            ;

stmt        : '\n'                  { ; }
            | assignment '\n'       { ; }
            | var eval              { driver.eval(*$1); }
            | var eval '(' tvar ')' { driver.eval(*$1); }
            | exp '\n'              { driver.print($1); }
            | lgc '\n'              { driver.print($1); }
            | quit '\n'             { exit(0); }
            | print exp '\n'        { driver.print($2); }
            | printenv '\n'         { driver.print_env(); }
            ;

eq_op       : exp EQ exp            { $1 == $3 ? $$ = true : $$ = false; }
            | exp GE exp            { $1 > $3  ? $$ = true : $$ = false; }
            | exp LE exp            { $1 < $3  ? $$ = true : $$ = false; }
            | exp GEQ exp           { $1 >= $3 ? $$ = true : $$ = false; }
            | exp LEQ exp           { $1 <= $3 ? $$ = true : $$ = false; }
            | '(' eq_op ')'         { ; }
            ;

lgc         : eq_op                 
            | t_not lgc %prec UNOT  { $$ = !($2); }
            | lgc t_and lgc         { $$ = $1 && $3; }
            | lgc t_or lgc          { $$ = $1 || $3; }
            | lgc implies lgc       { $$ = $1 ? $3 : false; }
            | forall lgc            { $$ = $2; } //TODO;
            | exists lgc            { $$ = $2; } //TODO;
            | '(' lgc ')'           { $$ = $2; } //TODO;
            ;

assignment  : var '=' exp           { driver.update_var(*$1, "real", $3); }
            | realnum var           { driver.update_var(*$2, "real", 0); } 
            | intnum var            { driver.update_var(*$2, "int", 0); } 
            | formula var           { driver.update_form(*$2, ""); } 
            | var define            { driver.update_form(*$1, *$2); }
            ;

tvar        : var '=' exp           { driver.update_temp(*$1, "real", $3); }
            | tvar ',' var '=' exp  { driver.update_temp(*$3, "real", $5); } 

exp         : term
            | '-' exp %prec UMINUS  { $$ = -$2; }
            | exp '+' exp           { $$ = $1 + $3; }
            | exp '-' exp           { $$ = $1 - $3; }
            | exp '*' exp           { $$ = $1 * $3; }
            | exp '/' exp           { $$ = $1 / $3; }
            | '(' exp ')'           { $$ = $2; }
            ;

term        : number                
            | var                   { $$ = driver.get_var(*$1); }
            ;


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
