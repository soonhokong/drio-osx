/* Author: Jichao Sun <jichaos@andrew.cmu.edu> 
 * Copyright 2014 Jichao Sun
 */

#include "types/formula/connective.h"

namespace shell{

fmla_cnct::fmla_cnct(unsigned type, const fmla* lhs, const fmla* rhs):
	f_type(type),
	f_lhs(lhs),
	f_rhs(rhs){ f_kind = Connective; }

bool fmla_cnct::val() const{
	switch(f_type){
		case And:
			return f_lhs->val() && f_rhs->val();
		case Or:
			return f_lhs->val() || f_rhs->val();
		case Implies:
			return f_lhs->val() ? f_rhs->val() : false; //TODO: Implemenet correct implies
	}
	//Should never reach here
	return false;
}

fmla_neg::fmla_neg(const fmla* arg):
	f_arg(arg) { f_kind = Negation; }
}