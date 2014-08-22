/* Author: Jichao Sun <jichaos@andrew.cmu.edu>
 * Copyright 2014 Jichao Sun
 */

#include <string>
#include <utility>
#include "types/formula/expr.h"
#include "types/formula/term.h"
#include "types/formula/function.h"
#include "types/formula/var_scoped_env.h"

namespace shell{

using std::cin;
using std::cout;
using std::cerr;
using std::string;
using std::make_pair;
using std::exception;

// Scoped environment for storing variables
dreal::var_scoped_env var_env;

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

/**** Start term interface ****/

expr mk_const(const double num){
    return mk_expr(new term_const(num));
}

// Used for delclaring variable type
void set_var(const string &name, term_type const type){
    double val;
    try{
        val = var_env.lookup(name).second;
    } catch(const exception& ex){
        val = 0;
    }
    var_env.insert(name, make_pair(type, val));
}

expr mk_var(const string &name){
    term_type type;
    try{
        type = var_env.lookup(name).first;
    } catch(const exception& ex){
        type = term_type::Real;
    }
    return mk_expr(new term_var(name, type));
}

void set_var(const string &name, expr t1){
    // Retrieving type if already delcared
    term_type type;
    try{
        type = var_env.lookup(name).first;
    } catch(const exception& ex){
        type = term_type::Real;
    }

    try {
        double num = t1.val();
        var_env.insert(name, make_pair(type, num));
    } catch(const exception& ex){
        cerr << ex.what() << "\n";
    }
}

expr mk_func(const func_op op, expr t1){
    return mk_expr(new term_func(op, t1));
}

expr mk_func(const func_op op, expr t1, expr t2){
    return mk_expr(new term_func(op, t1, t2));
}

expr mk_func(const trig_op op, expr t1){
    return mk_expr(new term_trig(op, t1));
}

void var_push(){
    var_env.push();
}

void var_pop(){
    var_env.pop();
}

void var_print_env(){
    for (auto i = var_env.begin(); i != var_env.end(); ++i){
        if (i->first != ""){
            cout << i->first << ":" << i->second.first << " ~ " << i->second.second << "\n";
        }
    }
}

void print_exp(const expr t){
    try{
        cout << t.val()  << "\n";
    } catch(const exception& ex){
        cerr << ex.what() << "\n";
    }
}
/**** End term interface ****/

term_var::term_var(string const name, term_type const type):
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
