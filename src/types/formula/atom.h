/* Author: Jichao Sun <jichaos@andrew.cmu.edu>
 * Copyright 2014 Jichao Sun, Soonho Kong
 */

#pragma once
#include "types/formula/term.h"
#include "types/formula/formula.h"

namespace shell{

/* Equality type atomic formula */
enum class equality_op { EQ, GT, LT, GTE, LTE };

class fmla_eq : public fmla_cell {
protected:
    equality_op         m_type;
    term          	    m_lhs;
    term          	    m_rhs;
public:
    fmla_eq(equality_op op, term lhs, term rhs);
    ~fmla_eq() { m_lhs.free(); m_rhs.free(); }
    equality_op type() const { return m_type; }
    bool val() const;
};
}
