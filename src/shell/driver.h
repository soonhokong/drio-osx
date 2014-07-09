/* Author: Jichao Sun <jichaos@andrew.cmu.edu> 
 * Copyright 2014 Jichao Sun
 */

#pragma once
#include <string>
#include "shell/scanner.h"
#include "parser.tab.hh"
#include "types/formula/term.h"
#include "types/formula/function.h"
#include "types/formula/atom.h"

namespace shell{

class driver{
public:
    driver() :   parser (nullptr),
                 scanner (nullptr){};

    virtual ~driver();

    void parse();

    void print_exp(const void *expr);
    void print_atom(const void *atom);
    void print_env();
    void set_var(const std::string &name, void *expr);

    // void update_form(const std::string &name, const std::string &form);
    // void update_temp(const std::string &var, const std::string &type, const double num);
    // void eval(const std::string &name);

    term* mk_const(const double num, const unsigned type);
    term* mk_var(const std::string &name, const unsigned type);
    term* mk_var(const std::string &name);
    term* mk_func(const unsigned op, const void *expr);
    term* mk_func(const unsigned op, const void *expr1, const void *expr2);

    atom* mk_atom_eq(const unsigned op, const void *arg1, const void *arg2);

private:
    shell::parser *parser;
    shell::scanner *scanner;
};
}
