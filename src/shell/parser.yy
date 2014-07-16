/* Author: Jichao Sun <jichaos@andrew.cmu.edu> 
 * Copyright 2014 Jichao Sun
 */

%skeleton "lalr1.cc"
%debug
%defines
%define namespace "shell"
%define parser_class_name "parser"

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

    enum term_type { Real, Int };
    enum func_op { Add, Sub, Mult, Div, Neg, Pow };
    enum equality_op { EQ, GT, LT, GTE, LTE };
    enum cnct_type { And, Or, Implies };
    enum quant_type { Forall, Exists };


    static int yylex(shell::parser::semantic_type *yylval,
                    shell::scanner  &scanner,
                    shell::driver   &driver);
}

%union {
    void *ptr; 
    double num;
    std::string *str;
}

%start          line

%token          realnum
%token          intnum
%token          GT
%token          LT
%token          GTE
%token          LTE
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

%type   <ptr>   exp term eq_op lgc
%left           '+' '-'
%left           '*' '/'
%nonassoc       UMINUS
%nonassoc       UNOT

%destructor { if ($$)  { delete ($$); ($$) = nullptr; } } <str>


%%
line        : stmt
            | line stmt
            ;

stmt        : '\n'                      { ; }
            | assignment '\n'           { ; }
            | var eval                  { driver.eval_fmla(*$1); } 
            | var eval '(' tmp_var ')'  { driver.eval_fmla(*$1); driver.var_pop(); }
            | exp '\n'                  { driver.print_exp($1); driver.free_exp($1); }
            | lgc '\n'                  { driver.print_fmla($1); driver.free_fmla($1); } 
            | quit '\n'                 { exit(0); }
            | print exp '\n'            { driver.print_exp($2); driver.free_exp($2); }
            | printenv '\n'             { driver.print_env(); }
            ;

eq_op       : exp EQ exp            { $$ = driver.mk_fmla_eq(EQ,$1,$3); } 
            | exp GT exp            { $$ = driver.mk_fmla_eq(GT,$1,$3); } 
            | exp LT exp            { $$ = driver.mk_fmla_eq(LT,$1,$3); } 
            | exp GTE exp           { $$ = driver.mk_fmla_eq(GTE,$1,$3); } 
            | exp LTE exp           { $$ = driver.mk_fmla_eq(LTE,$1,$3); } 
            | '(' eq_op ')'         { $$ = $2; }
            ;

lgc         : eq_op                 
            | t_not lgc %prec UNOT  { $$ = driver.mk_fmla_neg($2); } 
            | lgc t_and lgc         { $$ = driver.mk_fmla_cnct(And, $1, $3); } 
            | lgc t_or lgc          { $$ = driver.mk_fmla_cnct(Or, $1, $3); }
            | lgc implies lgc       { $$ = driver.mk_fmla_cnct(Implies, $1, $3); } 
            | forall var lgc        { $$ = driver.mk_fmla_quant(Forall, *$2, $3); } 
            | exists var lgc        { $$ = driver.mk_fmla_quant(Exists, *$2, $3); } 
            | '(' lgc ')'           { $$ = $2; } 
            ;

assignment  : var '=' exp           { driver.set_var(*$1, $3); }
            | realnum var           { driver.mk_var(*$2, Real); } 
            | intnum var            { driver.mk_var(*$2, Int); } 
            | formula var           { driver.set_fmla(*$2); }  
            | var define lgc        { driver.set_fmla(*$1,$3); }  
            | var define exp        { driver.error("Not a valid formula"); }
            ;

tmp_var     : var '=' exp               { driver.var_push(); driver.set_var(*$1, $3); } 
            | tmp_var ',' var '=' exp   { driver.set_var(*$3, $5); }
            ;

exp         : term
            | '-' exp %prec UMINUS  { $$ = driver.mk_func(Neg, $2); }
            | exp '+' exp           { $$ = driver.mk_func(Add, $1, $3); }
            | exp '-' exp           { $$ = driver.mk_func(Sub, $1, $3); }
            | exp '*' exp           { $$ = driver.mk_func(Mult, $1, $3); }
            | exp '/' exp           { $$ = driver.mk_func(Div, $1, $3); }
            | exp '^' exp           { $$ = driver.mk_func(Pow, $1, $3); }
            | '(' exp ')'           { $$ = $2; }
            ;

term        : number                { $$ = driver.mk_const($1); }
            | var                   { $$ = driver.mk_var(*$1); }
            ;
 

%%

// C++ Code:

void 
shell::parser::error( const shell::parser::location_type &l,
                      const std::string &err_message )
{
   std::cerr << "Error: " << err_message << "\n"; 
}

#include "scanner.h"

static int yylex( shell::parser::semantic_type *yylval,
                  shell::scanner  &scanner,
                  shell::driver   &driver ){
   return(scanner.yylex(yylval));
}
