/* Author: Jichao Sun <jichaos@andrew.cmu.edu>
 * Copyright 2014 Jichao Sun
 */

#include "types/formula/quantifier.h"
#include "types/formula/formula.h"
#include "types/formula/term.h"

namespace shell{

fmla_quant::fmla_quant(quant_op const op, term var, fmla formula):
        m_op(op),
        m_var(var),
        m_fmla(formula){ m_kind = formula_kind::Quantifier; }

bool fmla_quant::val() const{
        return m_fmla.val(); // TODO(jichaos): Implement quantifier solving
}
}
