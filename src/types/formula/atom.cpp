/* Author: Jichao Sun <jichaos@andrew.cmu.edu>
 * Copyright 2014 Jichao Sun
 */

#include "types/formula/atom.h"
#include "types/formula/formula.h"
#include "types/formula/term.h"

namespace shell{

fmla_eq::fmla_eq(equality_op op, const term *lhs, const term *rhs):
    f_type(op),
    f_lhs(lhs),
    f_rhs(rhs){ f_kind = formula_kind::Equality; }

bool fmla_eq::val() const{
    switch( f_type ){
    case equality_op::EQ:
        return f_lhs->val() == f_rhs->val();
    case equality_op::GT:
        return f_lhs->val() > f_rhs->val();
    case equality_op::LT:
        return f_lhs->val() < f_rhs->val();
    case equality_op::GTE:
        return f_lhs->val() >= f_rhs->val();
    case equality_op::LTE:
        return f_lhs->val() <= f_rhs->val();
    }
    //Should never reach here
    return false;
}
}
