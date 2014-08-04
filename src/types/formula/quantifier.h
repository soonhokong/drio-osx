/* Author: Jichao Sun <jichaos@andrew.cmu.edu>
 * Copyright 2014 Jichao Sun
 */

#pragma once
#include "types/formula/formula.h"
#include "types/formula/term.h"

namespace shell{

enum class quant_type { Forall, Exists };

class fmla_quant : public fmla_cell {
protected:
    quant_type          m_type;
    term           		m_var;
    fmla          		m_fmla;
public:
    fmla_quant(quant_type const op, term  var, fmla formula);
    ~fmla_quant() { m_var.free(); m_fmla.free(); }
    quant_type type() { return m_type; }
    bool val() const;
};
}
