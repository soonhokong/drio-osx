/* Author: Jichao Sun <jichaos@andrew.cmu.edu> 
 * Copyright 2014 Jichao Sun
 */

#include "types/formula/term.h"
#include "shell/scoped_env.h"

extern dreal::scoped_env var_env;

namespace shell{

term_var::term_var(std::string const name, unsigned const type):
	m_type(type),
	m_name(name){ m_kind = Variable; }

double term_var::val() const {
	term_var* res = var_env.lookup(m_name);
	if (res->type() == Int){
		return static_cast<int>(res->val() + 0.5);
	} else {
		return res->val();
	}
}

term_const::term_const(double const val, unsigned const type):
	m_type(type),
	m_val(val){ m_kind = Constant; }
}