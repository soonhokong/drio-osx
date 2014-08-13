/* Author: Jichao Sun <jichaos@andrew.cmu.edu>
 * Copyright 2014 Jichao Sun
 */

#pragma once
#include "types/formula/formula.h"
#include "types/formula/atom.h"

namespace shell{

enum class cnct_op { And, Or, Implies };

class fmla_cnct : public fmla_cell {
protected:
    cnct_op             m_op;
    expr                m_lhs;
    expr                m_rhs;
public:
    fmla_cnct(cnct_op const op, expr lhs, expr rhs);
    ~fmla_cnct() { m_lhs.free(); m_rhs.free(); }
    cnct_op op() const { return m_op; }
    bool eval() const;
};

class fmla_neg : public fmla_cell {
protected:
    expr                m_arg;
public:
    fmla_neg(expr arg);
    ~fmla_neg() { m_arg.free(); }
    bool eval() const { return !(m_arg.eval()); }
};
}
