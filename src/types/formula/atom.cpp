/* Author: Jichao Sun <jichaos@andrew.cmu.edu>
 * Copyright 2014 Jichao Sun
 */

#include <cassert>
#include "types/formula/atom.h"
#include "types/formula/formula.h"
#include "types/formula/term.h"

namespace shell{

fmla_eq::fmla_eq(equality_op op, term lhs, term rhs):
    m_op(op),
    m_lhs(lhs),
    m_rhs(rhs){ m_kind = formula_kind::Equality; }

bool fmla_eq::val() const {
    switch (m_op) {
    case equality_op::EQ:
        return m_lhs.val() == m_rhs.val();
    case equality_op::GT:
        return m_lhs.val() > m_rhs.val();
    case equality_op::LT:
        return m_lhs.val() < m_rhs.val();
    case equality_op::GTE:
        return m_lhs.val() >= m_rhs.val();
    case equality_op::LTE:
        return m_lhs.val() <= m_rhs.val();
    }
    assert(false); // should be unreachable
    return false;
}
}
