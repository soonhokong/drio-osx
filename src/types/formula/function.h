/* Author: Jichao Sun <jichaos@andrew.cmu.edu>
 * Copyright 2014 Jichao Sun
 */

#pragma once
#include <string>
#include <vector>
#include "types/formula/term.h"

namespace shell{

/* Function class for basic operations */
enum class func_op { Add, Sub, Mult, Div, Neg, Pow };

class term_func : public term_cell {
private:
    func_op             m_op;
    std::vector<expr>   m_expr;

public:
    term_func(const func_op op, expr t1);
    term_func(const func_op op, expr t1, expr t2);
    term_func(const func_op op, expr t1, expr t2, expr t3);
    ~term_func();
    double val() const;
    func_op op() const { return m_op; }
};

/* Function class for trig operations */
enum class trig_op { Sin, Cos, Tan, Asin, Acos, Atan, Sinh, Cosh, Tanh, Asinh, Acosh, Atanh};

class term_trig : public term_cell {
private:
    trig_op             m_op;
    expr                m_expr;
public:
    term_trig(const trig_op op, expr t1);
    ~term_trig() { m_expr.free(); }
    double val() const;
    trig_op op() const { return m_op; };
};
}
