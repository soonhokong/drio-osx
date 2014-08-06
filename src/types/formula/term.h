/* Author: Jichao Sun <jichaos@andrew.cmu.edu>
 * Copyright 2014 Jichao Sun
 */

#pragma once
#include <string>
#include <iostream>

namespace shell{

enum class term_kind { Variable, Constant, Formula };
enum class term_type { Real, Int };

std::ostream& operator<<(std::ostream & out, term_kind const & tk);
std::ostream& operator<<(std::ostream & out, term_type const & tt);

/* Abstract base class for terms */
class term_cell{
protected:
    term_kind        m_kind;
public:
    virtual ~term_cell() { }
    term_kind kind() const { return m_kind; }
    virtual double val() const =0;
};

/* Forward declare enums for term interface*/
enum class func_op;

class term{
private:
    term_cell*      m_ptr;
public:
    double val() const { return m_ptr->val(); }
    void free() { if (m_ptr) delete m_ptr; }
    term_kind kind() const { return m_ptr->kind(); }
    void* raw() const { return m_ptr; }

    friend term mk_term(term_cell* ptr);
};

term mk_const(const double num);
void set_var(const std::string &name, term_type const type);
term mk_var(const std::string &name);
void set_var(const std::string &name, term t1);
term mk_func(const func_op op, term t1);
term mk_func(const func_op op, term t1, term t2);

void var_push();
void var_pop();
void var_print_env();

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
