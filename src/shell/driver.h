/* Author: Jichao Sun <jichaos@andrew.cmu.edu> 
 * Copyright 2014 Jichao Sun
 */

#pragma once
#include <string>
#include "shell/scanner.h"
#include "parser.tab.hh"
#include "types/formula/term.h"
#include "types/formula/function.h"


namespace shell{

class driver{
public:
    driver() :   parser (nullptr),
                 scanner (nullptr){};

    virtual ~driver();

    void parse();

    void print(const void *expr);
    void print_env();
    void update_var(const std::string &var, void *expr);

    // void update_form(const std::string &name, const std::string &form);
    // void update_temp(const std::string &var, const std::string &type, const double num);
    // void eval(const std::string &name);

    term* mk_const(const double num, const unsigned type);
    term* mk_var(const std::string &name, const unsigned type);
    term* mk_func(const unsigned op, const void *expr);
    term* mk_func(const unsigned op, const void *expr1, const void *expr2);

private:
    shell::parser *parser;
    shell::scanner *scanner;
};
}
