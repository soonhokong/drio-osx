/* Author: Jichao Sun <jichaos@andrew.cmu.edu>
 * Copyright 2014 Jichao Sun
 */

#include "types/formula/connective.h"

namespace shell{

fmla_cnct::fmla_cnct(cnct_type type, const fmla* lhs, const fmla* rhs):
        f_type(type),
        f_lhs(lhs),
        f_rhs(rhs){ f_kind = formula_kind::Connective; }

bool fmla_cnct::val() const{
    switch(f_type){
    case cnct_type::And:
        return f_lhs->val() && f_rhs->val();
    case cnct_type::Or:
        return f_lhs->val() || f_rhs->val();
    case cnct_type::Implies:
        return f_lhs->val() ? f_rhs->val() : false; //TODO: Implemenet correct implies
    }
}

fmla_neg::fmla_neg(const fmla* arg):
    f_arg(arg) { f_kind = formula_kind::Negation; }
}
