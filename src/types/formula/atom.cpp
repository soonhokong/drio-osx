/* Author: Jichao Sun <jichaos@andrew.cmu.edu> 
 * Copyright 2014 Jichao Sun
 */

#include "types/formula/atom.h"
#include "types/formula/term.h"

namespace shell{

atom_eq::atom_eq(unsigned op, const term *lhs, const term *rhs):
    a_op(op),
    a_lhs(lhs),
    a_rhs(rhs){ a_kind = op; }

bool atom_eq::val() const{
    switch( a_op ){
        case EQ:
            return a_lhs->val() == a_rhs->val();
        case GT:
            return a_lhs->val() > a_rhs->val();
        case LT:
            return a_lhs->val() < a_rhs->val();
        case GTE:
            return a_lhs->val() >= a_rhs->val();
        case LTE:
            return a_lhs->val() <= a_rhs->val();
    }
    //Should never reach here
    return false;
}
}