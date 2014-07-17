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
    cnct_type           f_type;
    const fmla*         f_lhs;
    const fmla*         f_rhs;
public:
    fmla_cnct(cnct_type type, const fmla* lsh, const fmla* rhs);
    ~fmla_cnct() { delete f_lhs; delete f_rhs; }
    cnct_type type() const { return f_type; }
    bool val() const;
};

class fmla_neg : public fmla {
protected:
    const fmla*      f_arg;
public:
    fmla_neg(const fmla* arg);
    ~fmla_neg() { delete f_arg; }
    bool val() const { return !(f_arg->val()); }
};
}
