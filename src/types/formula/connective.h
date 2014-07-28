/* Author: Jichao Sun <jichaos@andrew.cmu.edu>
 * Copyright 2014 Jichao Sun
 */

#pragma once
#include "types/formula/formula.h"
#include "types/formula/atom.h"

namespace shell{

enum class cnct_type { And, Or, Implies };

class fmla_cnct : public fmla {
protected:
    cnct_type           m_type;
    const fmla*         m_lhs;
    const fmla*         m_rhs;
public:
    fmla_cnct(cnct_type type, const fmla* lsh, const fmla* rhs);
    ~fmla_cnct() { delete m_lhs; delete m_rhs; }
    cnct_type type() const { return m_type; }
    bool val() const;
};

class fmla_neg : public fmla {
protected:
    const fmla*      m_arg;
public:
    fmla_neg(const fmla* arg);
    ~fmla_neg() { delete m_arg; }
    bool val() const { return !(m_arg->val()); }
};
}
