/* Author: Jichao Sun <jichaos@andrew.cmu.edu> 
 * Copyright 2014 Jichao Sun
 */

%{
#include <string>
#include <cstdlib>
#include "scanner.h"

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
">"                     { return token::GE; }
"<"                     { return token::LE; }
">="                    { return token::GEQ; }
"<="                    { return token::LEQ; }
"=="                    { return token::EQ; }

"formula"               { return token::formula; }
".eval"                 { return token::eval; }
":="[^\n]+              { 
                            yylval->str = STOKEN((yytext+=2));
                            return token::define; 
                        }

"and"                   { return token::t_and; }
"or"                    { return token::t_or; }
"implies"               { return token::implies; }
"not"                   
"forall"
"exists"

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
[-+=()*\n/]             { return yytext[0]; }

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
