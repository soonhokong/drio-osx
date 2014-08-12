/* Author: Jichao Sun <jichaos@andrew.cmu.edu>
 * Copyright 2014 Jichao Sun
 */

#include <string>
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

fmla mk_fmla(fmla_cell *ptr){
    fmla temp;
    temp.m_ptr = ptr;
    return temp;
}

fmla fmla_lookup(const std::string &name){
    return fmla_env.lookup(name);
}

fmla mk_fmla_eq(equality_op const op, term lhs, term rhs){
    return mk_fmla(new fmla_eq(op, lhs, rhs));
}

fmla mk_fmla_cnct(cnct_op const op, fmla lhs, fmla rhs){
    return mk_fmla(new fmla_cnct(op, lhs, rhs));
}

fmla mk_fmla_neg(fmla f1){
    return mk_fmla(new fmla_neg(f1));
}

fmla mk_fmla_quant(quant_op const op, const string &name, fmla formula){
    return mk_fmla(new fmla_quant(op, mk_var(name), formula));
}

void set_fmla(const string &name){
    fmla_env.insert(name, mk_fmla(NULL));
}

void set_fmla(const string &name, fmla formula){
    fmla_env.insert(name, formula);
}

void print_fmla(const fmla f){
    try{
        cout << (f.val() ? "true" : "false") << "\n";
    } catch(const exception& ex){
        cerr << ex.what() << "\n";
    }
}

void eval_fmla(const string &name){
    try{
        fmla formula = fmla_lookup(name);
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
