/* Author: Jichao Sun <jichaos@andrew.cmu.edu>
 * Copyright 2014 Jichao Sun, Soonho Kong
 */

#pragma once
#include "types/formula/term.h"
#include "types/formula/formula.h"

namespace shell{

/* Equality type atomic formula */
enum class equality_op { EQ, GT, LT, GTE, LTE };

class fmla_eq : public fmla {
protected:
    equality_op         f_type;
    const term*         f_lhs;
    const term*         f_rhs;
public:
    fmla_eq(equality_op op, const term *lhs, const term *rhs);
    ~fmla_eq() { delete f_lhs; delete f_rhs; }
    equality_op type() const { return f_type; }
    bool val() const;
};
}
