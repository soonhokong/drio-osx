/* Author: Jichao Sun <jichaos@andrew.cmu.edu>
 * Copyright 2014 Jichao Sun
 */

#pragma once
#include <iostream>

namespace shell{

class expr_cell {
public:
    virtual ~expr_cell() { }
    virtual double val() const { std::cerr << "Error: calling unimplemented .val()\n"; return 0;}
    virtual bool eval() const { std::cerr << "Error: calling unimplemented .eval()\n"; return false;}
};

class expr{
private:
    expr_cell*          m_ptr;
public:
    /** Interface for terms **/
    double val() const { return m_ptr->val(); }

    /** Interface for formulas **/
    bool eval() const { return m_ptr->eval(); }
    bool is_empty() const { return m_ptr == NULL; }

    /** Utility functiions **/
    friend expr mk_expr(expr_cell* ptr);
    void free() { if (m_ptr) delete m_ptr; }
    expr_cell* raw() const { return m_ptr; }
};

expr mk_expr(expr_cell* ptr);
}
