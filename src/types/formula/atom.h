/* Author: Jichao Sun <jichaos@andrew.cmu.edu> 
 * Copyright 2014 Jichao Sun
 */

#pragma once
#include "types/formula/term.h"
#include "types/formula/formula.h"

namespace shell{

/* Equality type atomic formula */
enum equality_op { EQ, GT, LT, GTE, LTE };

class fmla_eq : public fmla {
protected:
    unsigned            f_op;
    const term*         f_lhs;
    const term*         f_rhs;
public:
    fmla_eq(unsigned op, const term *lhs, const term *rhs);
    equality_op kind() const { return static_cast<equality_op>(f_op); }
    bool val() const;
};
}