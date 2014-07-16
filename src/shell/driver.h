/* Author: Jichao Sun <jichaos@andrew.cmu.edu> 
 * Copyright 2014 Jichao Sun
 */

#pragma once
#include <string>
#include "shell/scanner.h"
#include "parser.tab.hh"
#include "types/formula/term.h"
#include "types/formula/function.h"
#include "types/formula/formula.h"
#include "types/formula/atom.h"
#include "types/formula/connective.h"
#include "types/formula/quantifier.h"

namespace shell{

class driver{
public:
    driver() :   parser (nullptr),
                 scanner (nullptr){};

    virtual ~driver();

    void parse();

    void print_exp(const void *expr);
    void print_fmla(const void *fmla);
    void print_env();
    void set_var(const std::string &name, const void *expr);

    void var_push();
    void var_pop();

    // void update_form(const std::string &name, const std::string &form);
    // void update_temp(const std::string &var, const std::string &type, const double num);
    // void eval(const std::string &name);

    term* mk_const(const double num);
    term* mk_var(const std::string &name, const unsigned type);
    term* mk_var(const std::string &name);
    term* mk_func(const unsigned op, const void *expr);
    term* mk_func(const unsigned op, const void *expr1, const void *expr2);

    fmla* mk_fmla_eq(const unsigned op, const void *lhs, const void *rhs);
    fmla* mk_fmla_cnct(const unsigned op, const void *lhs, const void *rhs);
    fmla* mk_fmla_neg(const void *arg);
    fmla* mk_fmla_quant(const unsigned op, const std::string &name, const void *formula);

    void set_fmla(const std::string &name);
    void set_fmla(const std::string &name, const void *formula);
    void eval_fmla(const std::string &name);

    void free_exp(const void *expr);
    void free_fmla(const void *formula);

    void error(const std::string &err);

private:
    shell::parser *parser;
    shell::scanner *scanner;
};
}
