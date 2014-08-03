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

fmla mk_fmla_eq(equality_op const op, const term lhs, const term rhs){
    return mk_fmla(new fmla_eq(op, lhs, rhs));
}

fmla mk_fmla_cnct(cnct_type const op, const fmla lhs, const fmla rhs){
    return mk_fmla(new fmla_cnct(op, lhs, rhs));
}

fmla mk_fmla_neg(const fmla f1){
    return mk_fmla(new fmla_neg(f1));
}

fmla mk_fmla_quant(quant_type const op, const string &name, const fmla formula){
    return mk_fmla(new fmla_quant(op, mk_var(name), formula));
}

void set_fmla(const string &name){
    fmla_env.insert(name, mk_fmla(NULL));
}

void set_fmla(const string &name, const fmla formula){
    fmla_env.insert(name, formula);
}
}
