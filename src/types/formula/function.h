/* Author: Jichao Sun <jichaos@andrew.cmu.edu>
 * Copyright 2014 Jichao Sun
 */

#pragma once
#include <string>
#include "types/formula/term.h"

namespace shell{

/* Function class for unary and binary operations */
enum class func_op { Add, Sub, Mult, Div, Neg, Pow };

class term_func : public term {
private:
    func_op         m_op;
    unsigned        m_num_args;
    const term*     m_lhs;
    const term*     m_rhs;

public:
    term_func(const func_op op, const term *lhs);
    term_func(const func_op op, const term *lhs, const term *rhs);
    ~term_func() { delete m_lhs; delete m_rhs; }
    double val() const;
};
}
