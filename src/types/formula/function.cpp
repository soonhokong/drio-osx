/* Author: Jichao Sun <jichaos@andrew.cmu.edu>
 * Copyright 2014 Jichao Sun
 */

#include <string>
#include <cassert>
#include <cmath>
#include <vector>
#include "types/formula/function.h"

namespace shell{

term_func::term_func(const func_op op, term t1):
    m_op(op),
    m_trm(1) { m_kind = term_kind::Formula; m_trm[0] = t1; }

term_func::term_func(const func_op op, term t1, term t2):
    m_op(op),
    m_trm(2){ m_kind = term_kind::Formula; m_trm[0] = t1; m_trm[1] = t2;}

term_func::term_func(const func_op op, term t1, term t2, term t3):
    m_op(op),
    m_trm(3){ m_kind = term_kind::Formula; m_trm[0] = t1; m_trm[1] = t2; m_trm[3] = t3;}

term_func::~term_func(){
    for (int i = 0; i < m_trm.size(); ++i){
        m_trm[i].free();
    }
};

double term_func::val() const {
    switch (m_op){
    case func_op::Add:
        assert(m_trm.size() == 2);
        return m_trm[0].val() + m_trm[1].val();
    case func_op::Sub:
        assert(m_trm.size() == 2);
        return m_trm[0].val() - m_trm[1].val();
    case func_op::Mult:
        assert(m_trm.size() == 2);
        return m_trm[0].val() * m_trm[1].val();
    case func_op::Div:
        assert(m_trm.size() == 2);
        return m_trm[0].val() / m_trm[1].val();
    case func_op::Pow:
        assert(m_trm.size() == 2);
        return std::pow(m_trm[0].val(), m_trm[1].val());
    case func_op::Neg:
        return m_trm[0].val() * -1;
    }
    assert(false); // should be unreachable
    return 0;
}
}
