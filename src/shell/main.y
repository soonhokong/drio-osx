%{

#include <stdio.h>
#include <stdlib.h>

typedef struct var {
	double num;
	int set;
	char name;
} var;

void yyerror(char *s);
double getVar(char var);
void update_var(char var, double num);
void print_env();
extern int yylineno;

// Only supports single character variables for now...
var vars[52];
%}

%union {
	double num; 
	char var;
}
%start stmt
%token print  
%token printenv
%token quit
%token <num> number
%token <var> variable
%type <num> stmt exp term
%type <var> assignment
%left '+' '-'
%left '*' '/'
%nonassoc UMINUS 

%%
stmt	 	: assignment '\n'		{ ; }
			| exp '\n'				{ printf("%f\n", $1); }
			| quit '\n'				{ exit(0); }
			| print exp '\n'		{ printf("%f\n", $2); }
			| printenv '\n' 		{ print_env(); }
			| stmt exp '\n'			{ printf("%f\n", $2); }
			| stmt assignment '\n'	{ ; }
			| stmt quit	'\n'		{ exit(0); }
			| stmt print exp '\n'	{ printf("%f\n", $3); }
			| stmt printenv '\n'	{ print_env(); }
			;

assignment	: variable '=' exp 		{ update_var($1,$3);}
			;

exp			: term 				
			| '-' exp %prec UMINUS 	{ $$ = -$2; }
			| exp '+' exp 			{ $$ = $1 + $3; }
			| exp '-' exp 			{ $$ = $1 - $3; }
			| exp '*' exp 			{ $$ = $1 * $3; }
			| exp '/' exp 			{ $$ = $1 / $3; }
			| '(' exp ')' 			{ $$ = $2; }
			;

term 		: number			
			| variable 				{ $$ = getVar($1); }
%%

// C Code:

int getIndex(char var){
	if (65 <= var && var <= 90){
		return var - 65;
	} else if (97 <= var && var <= 122){
		return var - 71;
	} else {
		printf("Error: Variable '%c' is not a valid variable. Defaulting to 0\n", var);
		return 0;
	}	
}

double getVar(char var){
	if (vars[getIndex(var)].set) {
		return vars[getIndex(var)].num;
	} else {
		printf("Error: Variable '%c' has not been assigned. Defaulting to 0\n", var);
		return 0;
	}
}

void update_var(char var, double num){
	vars[getIndex(var)].set = 1;
	vars[getIndex(var)].num = num;
	vars[getIndex(var)].name = var;
}

void print_env(){
	for (int i = 0; i < 52; ++i){
			if (vars[i].set)
				printf("%c:real ~ %f\n", vars[i].name, vars[i].num);
	}
}

void yyerror(char *s){
	fprintf(stderr, "Line %d: %s\n", yylineno, s);
}

int main(void){
	for (int i = 0; i < 52; ++i){
		vars[i].set = 0;
	}
	return yyparse();
}
