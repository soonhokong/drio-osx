/* Author: Jichao Sun <jichaos@andrew.cmu.edu> 
 * Copyright 2014 Jichao Sun
 */

#pragma once
#include <string>

namespace shell{

/* Abstract base class for terms */
enum term_kind { Variable, Constant, Formula };

class term{
protected:
    unsigned        m_kind;
public:
    term_kind kind() const { return static_cast<term_kind>(m_kind); }
    virtual double val() const =0;
};

/* Variable class */
enum term_type { Real, Int };

class term_var : public term {
private:
    unsigned        m_type;
    std::string     m_name;
public:
    term_var(const std::string name, const unsigned type); 

    term_type type() const { return static_cast<term_type>(m_type); }
    void set_type(unsigned type) { m_type = type; }
    std::string name() const { return m_name; }
    double val() const; 
};

/* Constants class */
class term_const : public term {
private:
    unsigned        m_type;
    double          m_val;
public:
    term_const(const double val, const unsigned type);

    term_type type() const { return static_cast<term_type>(m_type); }
    double val() const { return m_val; }
};
}