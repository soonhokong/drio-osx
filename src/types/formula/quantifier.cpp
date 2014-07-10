/* Author: Jichao Sun <jichaos@andrew.cmu.edu> 
 * Copyright 2014 Jichao Sun
 */

#include "types/formula/quantifier.h"
#include "types/formula/formula.h"
#include "types/formula/term.h"

namespace shell{

fmla_quant::fmla_quant(unsigned type, const term_var* var, const fmla* formula):
	f_type(type),
	f_var(var),
	f_fmla(formula){ f_kind = Quantifier; }

bool fmla_quant::val() const{
	return f_fmla->val(); //TODO Implement quantifier solving 
}

}