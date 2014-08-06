/* Author: Jichao Sun <jichaos@andrew.cmu.edu>
 * Copyright 2014 Jichao Sun
 */

#pragma once
#include <string>
#include "types/formula/term.h"

namespace shell{

/* Function class for unary and binary operations */
enum class func_op { Add, Sub, Mult, Div, Neg, Pow };

class term_func : public term_cell {
private:
    func_op         m_op;
    unsigned        m_num_args;
    term            m_lhs;
    term            m_rhs;

public:
    term_func(const func_op op, term lhs);
    term_func(const func_op op, term lhs, term rhs);
    ~term_func() { m_lhs.free(); if (m_num_args == 2) m_rhs.free(); }
    double val() const;
};
}
