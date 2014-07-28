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
    quant_type          m_type;
    const term_var*     m_var;
    const fmla*         m_fmla;
public:
    fmla_quant(quant_type const op, const term_var *var, const fmla *formula);
    ~fmla_quant() { delete m_var; }
    quant_type type() { return m_type; }
    bool val() const;
};
}
