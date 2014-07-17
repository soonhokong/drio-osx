/* Author: Jichao Sun <jichaos@andrew.cmu.edu>
 * Copyright 2014 Jichao Sun
 */

#include <utility>
#include "types/formula/term.h"
#include "shell/var_scoped_env.h"

extern dreal::var_scoped_env var_env;

namespace shell{

std::ostream& operator<<(std::ostream & out, term_kind const & tk) {
    switch (tk) {
    case term_kind::Variable:
        out << "Variable";
        break;
    case term_kind::Constant:
        out << "Constant";
        break;
    case term_kind::Formula:
        out << "Formula";
        break;
    }
    return out;
}

std::ostream& operator<<(std::ostream & out, term_type const & tt) {
    switch (tt) {
    case term_type::Real:
        out << "Real";
        break;
    case term_type::Int:
        out << "Int";
        break;
    }
    return out;
}

term_var::term_var(std::string const name, term_type const type):
    m_type(type),
    m_name(name){ m_kind = term_kind::Variable; }

double term_var::val() const {
    std::pair<shell::term_type, double> res = var_env.lookup(m_name);
    if (res.first == term_type::Int){
        return static_cast<int>(res.second + 0.5);
    } else {
        return res.second;
    }
}

term_const::term_const(double const val):
    m_val(val){ m_kind = term_kind::Constant; }
}
