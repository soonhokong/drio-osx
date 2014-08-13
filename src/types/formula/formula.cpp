/* Author: Jichao Sun <jichaos@andrew.cmu.edu>
 * Copyright 2014 Jichao Sun
 */

#include <string>
#include "types/formula/expr.h"
#include "types/formula/term.h"
#include "types/formula/function.h"
#include "types/formula/formula.h"
#include "types/formula/atom.h"
#include "types/formula/connective.h"
#include "types/formula/quantifier.h"
#include "types/formula/fmla_scoped_env.h"

using std::string;
using std::cout;
using std::cerr;
using std::exception;

namespace shell{

dreal::fmla_scoped_env fmla_env;

expr fmla_lookup(const std::string &name){
    return fmla_env.lookup(name);
}

expr mk_fmla_eq(equality_op const op, expr lhs, expr rhs){
    return mk_expr(new fmla_eq(op, lhs, rhs));
}

expr mk_fmla_cnct(cnct_op const op, expr lhs, expr rhs){
    return mk_expr(new fmla_cnct(op, lhs, rhs));
}

expr mk_fmla_neg(expr f1){
    return mk_expr(new fmla_neg(f1));
}

expr mk_fmla_quant(quant_op const op, const string &name, expr f1){
    return mk_expr(new fmla_quant(op, mk_var(name), f1));
}

void set_fmla(const string &name){
    fmla_env.insert(name, mk_expr(NULL));
}

void set_fmla(const string &name, expr f1){
    fmla_env.insert(name, f1);
}

void print_fmla(const expr f1){
    try{
        cout << (f1.eval() ? "true" : "false") << "\n";
    } catch(const exception& ex){
        cerr << ex.what() << "\n";
    }
}

void eval_fmla(const string &name){
    try{
        expr formula = fmla_lookup(name);
        if (formula.is_empty()){
            cerr << "Error: formula " << name << " was not found.\n";
        } else {
            print_fmla(formula);
        }
    } catch(const exception& ex){
        cerr << ex.what() << "\n";
    }
}
}
