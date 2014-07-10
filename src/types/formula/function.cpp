/* Author: Jichao Sun <jichaos@andrew.cmu.edu> 
 * Copyright 2014 Jichao Sun
 */

#include <string>
#include <cmath>
#include "types/formula/function.h"

namespace shell{

term_func::term_func(const unsigned op, const term *lhs):
    m_op(op),
    m_num_args(1),
    m_lhs(lhs){ m_kind = Formula; }

term_func::term_func(const unsigned op, const term *lhs, const term *rhs):
    m_op(op),
    m_num_args(2),
    m_lhs(lhs),
    m_rhs(rhs){ m_kind = Formula; };

double term_func::val() const {
    switch (m_op){
        case Add:
            return m_lhs->val() + m_rhs->val();
        case Sub:
            return m_lhs->val() - m_rhs->val();
        case Mult:
            return m_lhs->val() * m_rhs->val();
        case Div:
            return m_lhs->val() / m_rhs->val();
        case Pow:
            return std::pow(m_lhs->val(), m_rhs->val());
        case Neg:
            return m_lhs->val() * -1;
    }
    //Should never reach here
    return 0;
}
}
