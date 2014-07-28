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
    equality_op         m_type;
    const term*         m_lhs;
    const term*         m_rhs;
public:
    fmla_eq(equality_op op, const term *lhs, const term *rhs);
    ~fmla_eq() { delete m_lhs; delete m_rhs; }
    equality_op type() const { return m_type; }
    bool val() const;
};
}
