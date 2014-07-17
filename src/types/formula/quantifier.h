/* Author: Jichao Sun <jichaos@andrew.cmu.edu>
 * Copyright 2014 Jichao Sun
 */

#pragma once
#include "types/formula/formula.h"
#include "types/formula/term.h"

namespace shell{

enum class quant_type { Forall, Exists };

class fmla_quant : public fmla {
protected:
    quant_type          f_type;
    const term_var*     f_var;
    const fmla*         f_fmla;
public:
    fmla_quant(quant_type const op, const term_var *var, const fmla *formula);
    ~fmla_quant() { delete f_var; }
    quant_type type() { return f_type; }
    bool val() const;
};
}
