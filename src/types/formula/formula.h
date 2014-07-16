/* Author: Jichao Sun <jichaos@andrew.cmu.edu> 
 * Copyright 2014 Jichao Sun
 */

#pragma once
#include "types/formula/term.h"

namespace shell{

/* Abstract base class for formulas */
enum formula_kind { Predicate, Equality, Negation, Connective, Quantifier, Custom };

class fmla {
protected:
	unsigned 			f_kind;
public:
	formula_kind kind() const { return static_cast<formula_kind>(f_kind); }
	virtual bool val() const =0;
	virtual void dealloc() const =0;
};
}