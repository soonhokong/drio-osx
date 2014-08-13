/* Author: Jichao Sun <jichaos@andrew.cmu.edu>
 * Copyright 2014 Jichao Sun
 */

#include <string>
#include <cassert>
#include <cmath>
#include <vector>
#include "types/formula/function.h"

namespace shell{

term_func::term_func(const func_op op, expr t1):
    m_op(op),
    m_expr(1) { m_kind = term_kind::Formula; m_expr[0] = t1; }

term_func::term_func(const func_op op, expr t1, expr t2):
    m_op(op),
    m_expr(2){ m_kind = term_kind::Formula; m_expr[0] = t1; m_expr[1] = t2;}

term_func::term_func(const func_op op, expr t1, expr t2, expr t3):
    m_op(op),
    m_expr(3){ m_kind = term_kind::Formula; m_expr[0] = t1; m_expr[1] = t2; m_expr[3] = t3;}

term_func::~term_func(){
    for (int i = 0; i < static_cast<int>(m_expr.size()); ++i){
        m_expr[i].free();
    }
};

double term_func::val() const {
    switch (m_op){
    case func_op::Add:
        assert(m_expr.size() == 2);
        return m_expr[0].val() + m_expr[1].val();
    case func_op::Sub:
        assert(m_expr.size() == 2);
        return m_expr[0].val() - m_expr[1].val();
    case func_op::Mult:
        assert(m_expr.size() == 2);
        return m_expr[0].val() * m_expr[1].val();
    case func_op::Div:
        assert(m_expr.size() == 2);
        return m_expr[0].val() / m_expr[1].val();
    case func_op::Pow:
        assert(m_expr.size() == 2);
        return std::pow(m_expr[0].val(), m_expr[1].val());
    case func_op::Neg:
        return m_expr[0].val() * -1;
    }
    assert(false); // should be unreachable
    return 0;
}
}
