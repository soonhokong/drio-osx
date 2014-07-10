/* Author: Jichao Sun <jichaos@andrew.cmu.edu> 
 * Copyright 2014 Jichao Sun
 */

#pragma once
#include <string>
#include "types/formula/term.h"

namespace shell{

/* Function class for unary and binary operations */
enum func_op { Add, Sub, Mult, Div, Neg, Pow };

class term_func : public term {
private:
    unsigned        m_op;
    unsigned        m_num_args;
    const term*     m_lhs;
    const term*     m_rhs;

public:
    term_func(const unsigned op, const term *lhs);
    term_func(const unsigned op, const term *lhs, const term *rhs);
    double val() const;
};
}