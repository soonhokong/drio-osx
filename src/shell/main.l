%{
#include "y.tab.h"
%}

%%
"print"					{ return print; }
"exit"			   		{ return quit; }
"print environment"		{ return printenv; }

	/* Variables */
[a-zA-Z]				{	
							yylval.var = yytext[0]; 
							return variable;
						}

	/* numbers */
[+-]?[0-9]*\.?[0-9]+	{
							yylval.num = atof(yytext); 
							return number;
						}

	/* operators */
[-+=()*\n/] 	 		{ return yytext[0]; }

	/* ignore spaces */
[ \t]               	{ ; }

	/* everything else */
.                     	{ yyerror ("unexpected character"); }

%%

int yywrap (void) {
	return 1;
}