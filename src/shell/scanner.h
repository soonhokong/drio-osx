/* Author: Jichao Sun <jichaos@andrew.cmu.edu> 
 * Copyright 2014 Jichao Sun
 */

#ifndef __SHELLSCANNER_HPP__
#define __SHELLSCANNER_HPP__ 1

// Defining yyFlexLexer
#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

// Changing default yylex function
#undef YY_DECL
#define YY_DECL int shell::scanner::yylex()

#include "parser.tab.hh"

namespace shell{

class scanner : public yyFlexLexer{
public:
    scanner() :  yyFlexLexer(),
                 yylval(nullptr){};

    int yylex(shell::parser::semantic_type *lval){
        yylval = lval;
        return(yylex());
    }

private:
    int yylex();

    // yylval is now a pointer to a union
    shell::parser::semantic_type *yylval;
};
}
#endif
