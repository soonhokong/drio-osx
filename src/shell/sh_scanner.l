/* Author: Jichao Sun <jichaos@andrew.cmu.edu> */

%{
#include <string>
#include <cstdlib>
#include "sh_scanner.hpp"

#define STOKEN(x) (new std::string(x))
#define NTOKEN(x) ( double (atof(x)) )
// #define yyterminate() return(token::END)
// #define YY_NO_UNISTD_H

typedef SH::SH_Parser::token token;

%}

%option debug
%option nodefault
%option yyclass="SH_Scanner" 
%option noyywrap 
%option c++

%%
"print"					{ return token::print; }
"exit"			   		{ return token::quit; }
"quit"			   		{ return token::quit; }
"print environment"		{ return token::printenv; }

	/* Variables */
[a-zA-Z]+				{	
							yylval->var = STOKEN(yytext); 
							return token::variable;
						}

	/* operators */
[-+=()*\n/] 	 		{ return yytext[0]; }

	/* numbers */
[0-9]*\.?[0-9]+			{
							yylval->num = NTOKEN(yytext); 
							return token::number;
						}

	/* ignore spaces */
[ \t]               	{ ; }

	/* everything else */
.                     	{ printf ("unexpected character"); }

%%

int yywrap (void) {
	return 1;
}
