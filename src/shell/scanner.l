/* Author: Jichao Sun <jichaos@andrew.cmu.edu>
 * Copyright 2014 Jichao Sun
 */

%{
#include <string>
#include <cstdlib>
#include "shell/scanner.h"
#include "types/formula/term.h"
#include "types/formula/formula.h"

#define STOKEN(x) (new std::string(x))
#define NTOKEN(x) ( double (atof(x)) )

typedef shell::parser::token token;
%}

%option debug
%option nodefault
%option yyclass="scanner"
%option noyywrap
%option c++

%%
"real"                  { return token::realnum; }
"int"                   { return token::intnum; }
">"                     { return token::GT; }
"<"                     { return token::LT; }
">="                    { return token::GTE; }
"<="                    { return token::LTE; }
"=="                    { return token::EQ; }

"sin"                   { return token::SIN; }
"cos"                   { return token::COS; }
"tan"                   { return token::TAN; }
"arcsin"                { return token::ASIN; }
"arccos"                { return token::ACOS; }
"arctan"                { return token::ATAN; }
"sinh"                  { return token::SINH; }
"cosh"                  { return token::COSH; }
"tanh"                  { return token::TANH; }
"arcsinh"               { return token::ASINH; }
"arccosh"               { return token::ACOSH; }
"arctanh"               { return token::ATANH; }

"\\and"                   { return token::t_and; }
"\\or"                    { return token::t_or; }
"\\implies"               { return token::implies; }
"\\not"                   { return token::t_not; }
"\\forall"                { return token::forall; }
"\\exists"                { return token::exists; }

"formula"               { return token::formula; }
".eval"                 { return token::eval; }
":="                    { return token::define; }

"print"                 { return token::print; }
"exit"                  { return token::quit; }
"quit"                  { return token::quit; }
"print environment"     { return token::printenv; }

    /* Variables */
[a-zA-Z]+               {
                            yylval->str = STOKEN(yytext);
                            return token::var;
                        }

    /* operators */
[-+=()*\n/,^]             { return yytext[0]; }

    /* numbers */
[0-9]*\.?[0-9]+         {
                            yylval->num = NTOKEN(yytext);
                            return token::number;
                        }

    /* ignore spaces */
[ \t]                   { ; }

    /* everything else */
.                       { printf ("unexpected character\n"); }

%%

int yywrap (void) {
    return 1;
}
