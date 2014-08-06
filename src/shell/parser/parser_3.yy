/* Author: Jichao Sun <jichaos@andrew.cmu.edu>
 * Copyright 2014 Jichao Sun
 * This parser file is to be used with Bison 3.0 and above.
 * It contains the same implementation as parser_2, but some changes syntactically.
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
    #include "types/formula/term.h"
    #include "types/formula/formula.h"
    #include "shell/scanner.h"
    #include "shell/driver.h"

    static int yylex(shell::parser::semantic_type *yylval,
                    shell::scanner  &scanner,
                    shell::driver   &driver);
}

%union {
    term trm;
    fmla fml;
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
%token          define

%token          print
%token          printenv
%token          quit

%token  <num>   number
%token  <str>   var

%type   <fml>   eq_op lgc
%type   <trm>   exp term

%left           t_and t_or implies t_not
%left           EQ GT LT GTE LTE
%left           '+' '-'
%left           '*' '/' '^'

%nonassoc       UMINUS
%nonassoc       UNOT

%destructor { if ($$)  { delete ($$); ($$) = nullptr; } } var

%expect 7

%%
line        : stmt '\n'
            | line stmt '\n'
            ;

stmt        : assignment                { ; }
            | var eval '(' ')'          { driver.eval_fmla(*$1); }
            | var eval '(' tmp_var ')'  { driver.eval_fmla(*$1); shell::var_pop(); }
            | exp                       { driver.print_exp($1); $1.free(); }
            | lgc                       { driver.print_fmla($1); $1.free(); }
            | quit                      { exit(0); }
            | print exp                 { driver.print_exp($2); $2.free(); }
            | printenv                  { shell::var_print_env(); }
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
            | lgc t_and lgc         { $$ = shell::mk_fmla_cnct(cnct_op::And, $1, $3); }
            | lgc t_or lgc          { $$ = shell::mk_fmla_cnct(cnct_op::Or, $1, $3); }
            | lgc implies lgc       { $$ = shell::mk_fmla_cnct(cnct_op::Implies, $1, $3); }
            | forall var lgc        { $$ = shell::mk_fmla_quant(quant_op::Forall, *$2, $3); }
            | exists var lgc        { $$ = shell::mk_fmla_quant(quant_op::Exists, *$2, $3); }
            | '(' lgc ')'           { $$ = $2; }
            ;

assignment  : var '=' exp           { shell::set_var(*$1, $3); $3.free(); }
            | realnum var           { shell::set_var(*$2, term_type::Real); }
            | intnum var            { shell::set_var(*$2, term_type::Int); }
            | formula var           { shell::set_fmla(*$2); }
            | var define lgc        { shell::set_fmla(*$1,$3); $3.free(); }
            | var define exp        { driver.error("Not a valid formula"); $3.free(); }
            ;

tmp_var     : var '=' exp               { shell::var_push(); shell::set_var(*$1, $3); $3.free(); }
            | tmp_var ',' var '=' exp   { shell::set_var(*$3, $5); $5.free(); }
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
shell::parser::error( const std::string &err_message )
{
   std::cerr << "Error: " << err_message << "\n";
}


static int yylex( shell::parser::semantic_type *yylval,
                  shell::scanner  &scanner,
                  shell::driver   &driver ){
   return(scanner.yylex(yylval));
}
