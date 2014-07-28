/* Author: Jichao Sun <jichaos@andrew.cmu.edu>
 * Copyright 2014 Jichao Sun
 */

#include <string>
#include <cassert>
#include <cmath>
#include "types/formula/function.h"

namespace shell{

term_func::term_func(const func_op op, const term lhs):
    m_op(op),
    m_num_args(1),
    m_lhs(lhs),
    m_rhs(){ m_kind = term_kind::Formula; }

term_func::term_func(const func_op op, const term lhs, const term rhs):
    m_op(op),
    m_num_args(2),
    m_lhs(lhs),
    m_rhs(rhs){ m_kind = term_kind::Formula; };

double term_func::val() const {
    switch (m_op){
    case func_op::Add:
        return m_lhs.val() + m_rhs.val();
    case func_op::Sub:
        return m_lhs.val() - m_rhs.val();
    case func_op::Mult:
        return m_lhs.val() * m_rhs.val();
    case func_op::Div:
        return m_lhs.val() / m_rhs.val();
    case func_op::Pow:
        return std::pow(m_lhs.val(), m_rhs.val());
    case func_op::Neg:
        return m_lhs.val() * -1;
    }
    assert(false); // should be unreachable
    return 0;
}
}
