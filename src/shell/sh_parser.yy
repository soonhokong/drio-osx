/* Author: Jichao Sun <jichaos@andrew.cmu.edu> 
 * Copyright 2014 Jichao Sun
 */

%skeleton "lalr1.cc"
%debug
%defines
%define api.namespace {SH}
%define parser_class_name {SH_Parser}

%code requires{
    namespace SH{
        class SH_Driver;
        class SH_Scanner;
    }
}

%lex-param   { SH_Scanner  &scanner  }
%parse-param { SH_Scanner  &scanner  }
 
%lex-param   { SH_Driver  &driver  }
%parse-param { SH_Driver  &driver  }

%code{
    #include <iostream>
    #include <cstdlib>
    #include "sh_driver.h"

   static int yylex(SH::SH_Parser::semantic_type *yylval,
                    SH::SH_Scanner  &scanner,
                    SH::SH_Driver   &driver);

// void yyerror(char *s);
// double getVar(char var);
// void update_var(char var, double num);
// void print_env();
// extern int yylineno;
}

%union {
    double num; 
    std::string *var;
}

%start          stmt
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
// line         : stmt 
//          | line stmt
//          ;

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

assignment  : variable '=' exp      { driver.update_var(*$1,$3); }
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
SH::SH_Parser::error( const std::string &err_message )
{
   std::cerr << "Error: " << err_message << "\n"; 
}

#include "sh_scanner.h"

static int yylex( SH::SH_Parser::semantic_type *yylval,
                  SH::SH_Scanner  &scanner,
                  SH::SH_Driver   &driver ){
   return(scanner.yylex(yylval));
}
