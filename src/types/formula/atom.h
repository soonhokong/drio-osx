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
    unsigned            f_type;
    const term*         f_lhs;
    const term*         f_rhs;
public:
    fmla_eq(unsigned op, const term *lhs, const term *rhs);
    equality_op type() const { return static_cast<equality_op>(f_type); }
    bool val() const;
    void dealloc() const { f_lhs->dealloc(); f_rhs->dealloc(); delete this; }
};
}