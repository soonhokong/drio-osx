/* Author: Jichao Sun <jichaos@andrew.cmu.edu>
 * Copyright 2014 Jichao Sun
 */

#pragma once
#include <string>
#include <iostream>
#include "types/formula/expr.h"

namespace shell{

enum class term_kind { Variable, Constant, Formula };
enum class term_type { Real, Int };

std::ostream& operator<<(std::ostream & out, term_kind const & tk);
std::ostream& operator<<(std::ostream & out, term_type const & tt);

/* Abstract base class for terms */
class term_cell : public expr_cell{
protected:
    term_kind        m_kind;
public:
    virtual ~term_cell() { }
    term_kind kind() const { return m_kind; }
};

/* Forward declare enums for term interface*/
enum class func_op;

expr mk_const(const double num);
void set_var(const std::string &name, term_type const type);
expr mk_var(const std::string &name);
void set_var(const std::string &name, expr t1);
expr mk_func(const func_op op, expr t1);
expr mk_func(const func_op op, expr t1, expr t2);

void var_push();
void var_pop();
void var_print_env();
void print_exp(const expr t);

/* Variable class */
class term_var : public term_cell {
private:
    term_type       m_type;
    std::string     m_name;
public:
    term_var(const std::string name, const term_type type);
    ~term_var() {};
    term_type type() const { return m_type; }
    void set_type(term_type type) { m_type = type; }
    std::string name() const { return m_name; }
    double val() const;
};

/* Constants class */
class term_const : public term_cell {
private:
    double          m_val;
public:
    term_const(const double val);
    ~term_const() {};
    double val() const { return m_val; }
};
}
