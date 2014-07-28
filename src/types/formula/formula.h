/* Author: Jichao Sun <jichaos@andrew.cmu.edu>
 * Copyright 2014 Jichao Sun
 */

#pragma once
#include "types/formula/term.h"

namespace shell{

/* Abstract base class for formulas */
enum class formula_kind { Predicate, Equality, Negation, Connective, Quantifier, Custom };

class fmla {
protected:
    formula_kind m_kind;
public:
    virtual bool val() const =0;
    formula_kind kind() const { return m_kind; }
    virtual ~fmla() { }
};
}
