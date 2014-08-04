/* Author: Jichao Sun <jichaos@andrew.cmu.edu>
 * Copyright 2014 Jichao Sun
 */

#include <cassert>
#include "types/formula/connective.h"

namespace shell{

fmla_cnct::fmla_cnct(cnct_type type, fmla lhs, fmla rhs):
        m_type(type),
        m_lhs(lhs),
        m_rhs(rhs){ m_kind = formula_kind::Connective; }

bool fmla_cnct::val() const {
    switch (m_type) {
    case cnct_type::And:
        return m_lhs.val() && m_rhs.val();
    case cnct_type::Or:
        return m_lhs.val() || m_rhs.val();
    case cnct_type::Implies:
        return m_lhs.val() ? m_rhs.val() : false; // TODO(jichaos): Implemenet correct implies
    }
    assert(false); // should be unreachable
    return false;
}

fmla_neg::fmla_neg(fmla arg):
    m_arg(arg) { m_kind = formula_kind::Negation; }
}
