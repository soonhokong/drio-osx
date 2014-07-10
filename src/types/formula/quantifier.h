/* Author: Jichao Sun <jichaos@andrew.cmu.edu> 
 * Copyright 2014 Jichao Sun
 */

#pragma once
#include "types/formula/formula.h"
#include "types/formula/term.h"

namespace shell{

enum quant_type { Forall, Exists };

class fmla_quant : public fmla {
protected:
    unsigned            f_type;
    const term_var*     f_var;
    const fmla*         f_fmla;
public:
    fmla_quant(unsigned type, const term_var *var, const fmla *formula);
    quant_type type() { return static_cast<quant_type>(f_type); }
    bool val() const;
};
}