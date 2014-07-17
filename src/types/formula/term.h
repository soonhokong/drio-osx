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
class term{
protected:
    term_kind        m_kind;
public:
    virtual ~term() { }
    term_kind kind() const { return static_cast<term_kind>(m_kind); }
    virtual double val() const =0;
};

/* Variable class */
class term_var : public term {
private:
    term_type       m_type;
    std::string     m_name;
public:
    term_var(const std::string name, const term_type type);
    ~term_var() { }
    term_type type() const { return static_cast<term_type>(m_type); }
    void set_type(term_type type) { m_type = type; }
    std::string name() const { return m_name; }
    double val() const;
};

/* Constants class */
class term_const : public term {
private:
    double          m_val;
public:
    term_const(const double val);
    ~term_const() { }
    double val() const { return m_val; }
};
}
