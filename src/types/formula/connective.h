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
    fmla                m_lhs;
    fmla                m_rhs;
public:
    fmla_cnct(cnct_op const op, fmla lsh, fmla rhs);
    ~fmla_cnct() { m_lhs.free(); m_rhs.free(); }
    cnct_op op() const { return m_op; }
    bool val() const;
};

class fmla_neg : public fmla_cell {
protected:
    fmla                m_arg;
public:
    fmla_neg(fmla arg);
    ~fmla_neg() { m_arg.free(); }
    bool val() const { return !(m_arg.val()); }
};
}
