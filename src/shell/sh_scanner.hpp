/* Author: Jichao Sun <jichaos@andrew.cmu.edu> */

#ifndef __SHSCANNER_HPP__
#define __SHSCANNER_HPP__ 1

// Defining yyFlexLexer
#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

// Changing default yylex function
#undef YY_DECL
#define YY_DECL int SH::SH_Scanner::yylex()

#include "sh_parser.tab.hh"

namespace SH{

class SH_Scanner : public yyFlexLexer{
public:

	SH_Scanner() :	yyFlexLexer(),
					yylval( nullptr ){};

	int yylex(SH::SH_Parser::semantic_type *lval){
		yylval = lval;
		return(yylex());
	}

private:
	int yylex();

	//yylval is now a pointer to a union
	SH::SH_Parser::semantic_type *yylval;
};
}
#endif
