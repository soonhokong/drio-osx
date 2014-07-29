/* Author: Jichao Sun <jichaos@andrew.cmu.edu>
 * Copyright 2014 Jichao Sun
 * This parser file is to be used with Bison 2.3 to 2.7.
 * It contains the same implementation as parser_3, but some changes syntactically.
 */

%{
    #include <iostream>
    #include <cstdlib>
    #include <string>
    #include "types/formula/term.h"
    #include "types/formula/formula.h"
    #include "shell/scanner.h"
    #include "shell/driver.h"

    enum term_type { Real, Int };
    enum func_op { Add, Sub, Mult, Div, Neg, Pow };
    enum equality_op { EQ, GT, LT, GTE, LTE };
    enum cnct_type { And, Or, Implies };
    enum quant_type { Forall, Exists };
%}

%skeleton "lalr1.cc"
%debug
%defines
%name-prefix="shell"
%define "parser_class_name" "parser"

%lex-param   { class scanner  &scanner  }
%parse-param { class scanner  &scanner  }

%lex-param   { class driver  &driver  }
%parse-param { class driver  &driver  }

%union {
    term trm;
    fmla fml;
    double num;
    std::string *str;
}

%{

static int yylex( shell::parser::semantic_type *yylval,
                  shell::scanner  &scanner,
                  shell::driver   &driver );
%}

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
%token          define

%token          print
%token          printenv
%token          quit

%token  <num>   number
%token  <str>   var

%type   <fml>   eq_op lgc
%type   <trm>   exp term
%left           '+' '-'
%left           '*' '/'

%nonassoc       UMINUS
%nonassoc       UNOT

%destructor { if ($$)  { delete ($$); ($$) = nullptr; } } var

%%
line        : stmt
            | line stmt
            ;

stmt        : '\n'                      { ; }
            | assignment '\n'           { ; }
            | var eval '(' ')'          { driver.eval_fmla(*$1); }
            | var eval '(' tmp_var ')'  { driver.eval_fmla(*$1); shell::var_pop(); }
            | exp '\n'                  { driver.print_exp($1); }
            | lgc '\n'                  { driver.print_fmla($1); }
            | quit '\n'                 { exit(0); }
            | print exp '\n'            { driver.print_exp($2); }
            | printenv '\n'             { shell::var_print_env(); }
            ;

eq_op       : exp EQ exp            { $$ = shell::mk_fmla_eq(equality_op::EQ,$1,$3); }
            | exp GT exp            { $$ = shell::mk_fmla_eq(equality_op::GT,$1,$3); }
            | exp LT exp            { $$ = shell::mk_fmla_eq(equality_op::LT,$1,$3); }
            | exp GTE exp           { $$ = shell::mk_fmla_eq(equality_op::GTE,$1,$3); }
            | exp LTE exp           { $$ = shell::mk_fmla_eq(equality_op::LTE,$1,$3); }
            | '(' eq_op ')'         { $$ = $2; }
            ;

lgc         : eq_op
            | t_not lgc %prec UNOT  { $$ = shell::mk_fmla_neg($2); }
            | lgc t_and lgc         { $$ = shell::mk_fmla_cnct(cnct_type::And, $1, $3); }
            | lgc t_or lgc          { $$ = shell::mk_fmla_cnct(cnct_type::Or, $1, $3); }
            | lgc implies lgc       { $$ = shell::mk_fmla_cnct(cnct_type::Implies, $1, $3); }
            | forall var lgc        { $$ = shell::mk_fmla_quant(quant_type::Forall, *$2, $3); }
            | exists var lgc        { $$ = shell::mk_fmla_quant(quant_type::Exists, *$2, $3); }
            | '(' lgc ')'           { $$ = $2; }
            ;

assignment  : var '=' exp           { shell::set_var(*$1, $3); }
            | realnum var           { shell::mk_var(*$2, term_type::Real); }
            | intnum var            { shell::mk_var(*$2, term_type::Int); }
            | formula var           { shell::set_fmla(*$2); }
            | var define lgc        { shell::set_fmla(*$1,$3); }
            | var define exp        { driver.error("Not a valid formula"); }
            ;

tmp_var     : var '=' exp               { shell::var_push(); shell::set_var(*$1, $3); }
            | tmp_var ',' var '=' exp   { shell::set_var(*$3, $5); }
            ;

exp         : term
            | '-' exp %prec UMINUS  { $$ = shell::mk_func(func_op::Neg, $2); }
            | exp '+' exp           { $$ = shell::mk_func(func_op::Add, $1, $3); }
            | exp '-' exp           { $$ = shell::mk_func(func_op::Sub, $1, $3); }
            | exp '*' exp           { $$ = shell::mk_func(func_op::Mult, $1, $3); }
            | exp '/' exp           { $$ = shell::mk_func(func_op::Div, $1, $3); }
            | exp '^' exp           { $$ = shell::mk_func(func_op::Pow, $1, $3); }
            | '(' exp ')'           { $$ = $2; }
            ;

term        : number                { $$ = shell::mk_const($1); }
            | var                   { $$ = shell::mk_var(*$1); }
            ;
%%

// C++ Code:

void
shell::parser::error( const shell::parser::location_type &l,
                      const std::string &err_message )
{
   std::cerr << "Error: " << err_message << "\n";
}


static int yylex( shell::parser::semantic_type *yylval,
                  shell::scanner  &scanner,
                  shell::driver   &driver ){
   return(scanner.yylex(yylval));
}
