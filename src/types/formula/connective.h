/* Author: Jichao Sun <jichaos@andrew.cmu.edu>
 * Copyright 2014 Jichao Sun
 */

#pragma once
#include "types/formula/formula.h"
#include "types/formula/atom.h"

namespace shell{

enum class cnct_type { And, Or, Implies };

class fmla_cnct : public fmla_cell {
protected:
    cnct_type           m_type;
    fmla                m_lhs;
    fmla                m_rhs;
public:
    fmla_cnct(cnct_type const type, fmla lsh, fmla rhs);
    ~fmla_cnct() { m_lhs.free(); m_rhs.free(); }
    cnct_type type() const { return m_type; }
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
