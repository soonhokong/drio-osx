/* Author: Jichao Sun <jichaos@andrew.cmu.edu>
 * Copyright 2014 Jichao Sun
 */

#include <cassert>
#include "types/formula/connective.h"

namespace shell{

fmla_cnct::fmla_cnct(cnct_op type, expr lhs, expr rhs):
        m_op(type),
        m_lhs(lhs),
        m_rhs(rhs){ m_kind = formula_kind::Connective; }

bool fmla_cnct::eval() const {
    switch (m_op) {
    case cnct_op::And:
        return m_lhs.eval() && m_rhs.eval();
    case cnct_op::Or:
        return m_lhs.eval() || m_rhs.eval();
    case cnct_op::Implies:
        return m_lhs.eval() ? m_rhs.eval() : false; // TODO(jichaos): Implemenet correct implies
    }
    assert(false); // should be unreachable
    return false;
}

fmla_neg::fmla_neg(expr arg):
    m_arg(arg) { m_kind = formula_kind::Negation; }
}
