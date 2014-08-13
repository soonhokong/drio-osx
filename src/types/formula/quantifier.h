/* Author: Jichao Sun <jichaos@andrew.cmu.edu>
 * Copyright 2014 Jichao Sun
 */

#pragma once
#include "types/formula/formula.h"
#include "types/formula/term.h"

namespace shell{

enum class quant_op { Forall, Exists };

class fmla_quant : public fmla_cell {
protected:
    quant_op            m_op;
    expr                m_var;
    expr                m_fmla;
public:
    fmla_quant(quant_op const op, expr  var, expr formula);
    ~fmla_quant() { m_var.free(); m_fmla.free(); }
    quant_op type() { return m_op; }
    bool eval() const;
    quant_op op() const { return m_op; }
};
}
