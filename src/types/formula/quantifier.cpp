/* Author: Jichao Sun <jichaos@andrew.cmu.edu>
 * Copyright 2014 Jichao Sun
 */

#include "types/formula/quantifier.h"
#include "types/formula/formula.h"
#include "types/formula/term.h"

namespace shell{

fmla_quant::fmla_quant(quant_type ty, const term_var* var, const fmla* formula):
        f_type(ty),
        f_var(var),
        f_fmla(formula){ f_kind = formula_kind::Quantifier; }

bool fmla_quant::val() const{
        return f_fmla->val(); // TODO(jichaos): Implement quantifier solving
}

}
