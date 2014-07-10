/* Author: Jichao Sun <jichaos@andrew.cmu.edu> 
 * Copyright 2014 Jichao Sun
 */

#include "types/formula/atom.h"
#include "types/formula/term.h"

namespace shell{

fmla_eq::fmla_eq(unsigned op, const term *lhs, const term *rhs):
    f_op(op),
    f_lhs(lhs),
    f_rhs(rhs){ f_kind = op; }

bool fmla_eq::val() const{
    switch( f_op ){
        case EQ:
            return f_lhs->val() == f_rhs->val();
        case GT:
            return f_lhs->val() > f_rhs->val();
        case LT:
            return f_lhs->val() < f_rhs->val();
        case GTE:
            return f_lhs->val() >= f_rhs->val();
        case LTE:
            return f_lhs->val() <= f_rhs->val();
    }
    //Should never reach here
    return false;
}
}