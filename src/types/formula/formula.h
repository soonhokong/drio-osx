/* Author: Jichao Sun <jichaos@andrew.cmu.edu>
 * Copyright 2014 Jichao Sun
 */

#pragma once
#include <string>
#include "types/formula/term.h"
#include "types/formula/expr.h"

namespace shell{

enum class formula_kind { Predicate, Equality, Negation, Connective, Quantifier, Custom };

/* Abstract base class for formulas */
class fmla_cell : public expr_cell {
protected:
    formula_kind    m_kind;
public:
    formula_kind kind() const { return m_kind; }
    virtual ~fmla_cell() { }
};

/* Forward declare enums for fmla interface*/
enum class equality_op;
enum class cnct_op;
enum class quant_op;

expr fmla_lookup(const std::string &name);
expr mk_fmla_eq(equality_op const op, expr lhs, expr rhs);
expr mk_fmla_cnct(cnct_op const op, expr lhs, expr rhs);
expr mk_fmla_neg(expr f1);
expr mk_fmla_quant(quant_op const op, const std::string &name, expr formula);
void set_fmla(const std::string &name);
void set_fmla(const std::string &name, expr formula);

void print_fmla(const expr f);
void eval_fmla(const std::string &name);
}
