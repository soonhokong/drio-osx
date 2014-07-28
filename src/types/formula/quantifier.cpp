/* Author: Jichao Sun <jichaos@andrew.cmu.edu>
 * Copyright 2014 Jichao Sun
 */

#include "types/formula/quantifier.h"
#include "types/formula/formula.h"
#include "types/formula/term.h"

namespace shell{

fmla_quant::fmla_quant(quant_type const op, const term var, const fmla formula):
        m_type(op),
        m_var(var),
        m_fmla(formula){ m_kind = formula_kind::Quantifier; }

bool fmla_quant::val() const{
        return m_fmla.val(); // TODO(jichaos): Implement quantifier solving
}
}
