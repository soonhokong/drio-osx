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


    enum class term_type { Real, Int };
    enum class func_op { Add, Sub, Mult, Div, Neg, Pow };

    static int yylex(shell::parser::semantic_type *yylval,
                    shell::scanner  &scanner,
                    shell::driver   &driver);
}

%union {
    void *trm; 
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

%type   <trm>   exp term
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
            | var eval              { ; } //driver.eval(*$1);
            | exp '\n'              { driver.print($1); }
            | lgc '\n'              {  } //driver.print($1);
            | quit '\n'             { exit(0); }
            | print exp '\n'        { driver.print($2); }
            | printenv '\n'         { driver.print_env(); }
            ;

eq_op       : exp EQ exp            {  } //$1 == $3 ? $$ = true : $$ = false;
            | exp GT exp            {  } //$1 > $3  ? $$ = true : $$ = false;
            | exp LT exp            {  } //$1 < $3  ? $$ = true : $$ = false;
            | exp GTE exp           {  } //$1 >= $3 ? $$ = true : $$ = false;
            | exp LTE exp           {  } //$1 <= $3 ? $$ = true : $$ = false;
            | '(' eq_op ')'         { ; }
            ;

lgc         : eq_op                 
            | t_not lgc %prec UNOT  {  } //$$ = !($2);
            | lgc t_and lgc         {  } //$$ = $1 && $3;
            | lgc t_or lgc          {  } //$$ = $1 || $3;
            | lgc implies lgc       {  } //$$ = $1 ? $3 : false;
            | forall lgc            {  } //TODO; $$ = $2;
            | exists lgc            {  } //TODO; $$ = $2;
            | '(' lgc ')'           {  } //TODO; $$ = $2;
            ;

assignment  : var '=' exp           { driver.set_var(*$1, $3); }
            | realnum var           { driver.mk_var(*$2, Real); } 
            | intnum var            { driver.mk_var(*$2, Int); } 
            | formula var           { ; }  //driver.update_form(*$2, "")
            | var define            { ; }  //driver.update_form(*$1, *$2)
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

term        : number                { $$ = driver.mk_const($1, Real); }
            | var                   { $$ = driver.mk_var(*$1); }
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
