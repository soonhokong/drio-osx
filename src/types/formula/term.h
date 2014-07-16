/* Author: Jichao Sun <jichaos@andrew.cmu.edu> 
 * Copyright 2014 Jichao Sun
 */

#pragma once
#include <string>

namespace shell{

enum term_kind { Variable, Constant, Formula };
enum term_type { Real, Int };

/* Abstract base class for terms */
class term{
protected:
    unsigned        m_kind;
public:
    term_kind kind() const { return static_cast<term_kind>(m_kind); }
    virtual double val() const =0;
    virtual void dealloc() const =0;
};

/* Variable class */
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
    void dealloc() const { delete this; }
};

/* Constants class */
class term_const : public term {
private:
    double          m_val;
public:
    term_const(const double val);
    double val() const { return m_val; }
    void dealloc() const { delete this; }
};
}
