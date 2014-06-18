%{
#include "main.h"
%}

%%
"print"					{ return print; }
"exit"			   		{ return quit; }
"quit"			   		{ return quit; }
"print environment"		{ return printenv; }

	/* Variables */
[a-zA-Z]				{	
							yylval.var = yytext[0]; 
							return variable;
						}

	/* operators */
[-+=()*\n/] 	 		{ return yytext[0]; }

	/* numbers */
[0-9]*\.?[0-9]+			{
							yylval.num = atof(yytext); 
							return number;
						}

	/* ignore spaces */
[ \t]               	{ ; }

	/* everything else */
.                     	{ yyerror ("unexpected character"); }

%%

int yywrap (void) {
	return 1;
}