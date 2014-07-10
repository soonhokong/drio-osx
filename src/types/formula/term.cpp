/* Author: Jichao Sun <jichaos@andrew.cmu.edu> 
 * Copyright 2014 Jichao Sun
 */

#include <utility>
#include "types/formula/term.h"
#include "shell/scoped_env.h"

extern dreal::scoped_env var_env;

namespace shell{

term_var::term_var(std::string const name, unsigned const type):
    m_type(type),
    m_name(name){ m_kind = Variable; }

double term_var::val() const {
    std::pair<shell::term_type, double> res = var_env.lookup(m_name);
    if (res.first == Int){
        return static_cast<int>(res.second + 0.5);
    } else {
        return res.second;
    }
}

term_const::term_const(double const val):
    m_val(val){ m_kind = Constant; }
}