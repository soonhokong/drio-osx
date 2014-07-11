/* Author: Jichao Sun <jichaos@andrew.cmu.edu> 
 * Copyright 2014 Jichao Sun
 */

#include <iostream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <utility>
#include "shell/driver.h"
#include "shell/var_scoped_env.h"
#include "shell/fmla_scoped_env.h"
#include "types/formula/term.h"
#include "types/formula/function.h"
#include "types/formula/atom.h"
#include "types/formula/connective.h"
#include "types/formula/quantifier.h"

#define toTerm(x,y) const shell::term* y =  static_cast<const shell::term*>(x)
#define toTermVar(x,y) const shell::term_var* y =  static_cast<const shell::term_var*>(x)
#define toFmla(x,y) const shell::fmla* y =  static_cast<const shell::fmla*>(x)

/* var_env  -> unordered map for variables
   fmla_env -> unordered map for formulas
   temp_env -> unordered map for temporary variables */
dreal::var_scoped_env var_env;
dreal::fmla_scoped_env fmla_env;
// dreal::scoped_env temp_env;

shell::driver::~driver(){
    delete scanner;
    scanner = nullptr;
    delete parser;
    parser = nullptr;
}

void shell::driver::parse(){
    delete scanner;
    scanner = new shell::scanner();
    delete parser;
    parser = new shell::parser(*scanner, *this);

    if (parser->parse() != 0){
        std::cerr << "Parse failed \n";
    }
}

void shell::driver::print_exp(const void* expr){
    toTerm(expr,res);
    try{
        std::cout << res->val()  << "\n";
    } catch(const std::exception& ex){
        std::cerr << ex.what() << "\n";
    }
}

void shell::driver::print_fmla(const void* formula){
    toFmla(formula,res);
    try{
        std::cout << (res->val() ? "true" : "false") << "\n";
    } catch(const std::exception& ex){
        std::cerr << ex.what() << "\n";
    }
}

void shell::driver::print_env(){
    for (auto i = var_env.begin(); i != var_env.end(); ++i){
        if (i->first != ""){
            std::cout << i->first << ":" << i->second.first << " ~ " << i->second.second << "\n";
        }
    }
}

void shell::driver::set_var(const std::string &name, const void *expr){
    toTerm(expr,res);

    //Retrieving type if already delcared
    term_type type;
    try{
        type = var_env.lookup(name).first;
    } catch(const std::exception& ex){
        type = Real;
    }
    
    try {
        double num = res->val();
        var_env.insert(name, std::make_pair(type,num));
    } catch(const std::exception& ex){
        std::cerr << ex.what() << "\n";
    }
}

shell::term* shell::driver::mk_const(const double num){
    return new term_const(num);
}

//Used for delclaring variable type
shell::term* shell::driver::mk_var(const std::string &name, const unsigned type){
    term_var * res = new term_var(name, type);
    var_env.insert(name, std::make_pair(static_cast<term_type>(type),0));
    return res;
}

//Single arg constructor for possibly inheriting a already declared type.
shell::term* shell::driver::mk_var(const std::string &name){
    term_type type;
    try{
        type = var_env.lookup(name).first;
    } catch(const std::exception& ex){
        type = Real;
    }
    return new term_var(name, type);
}

shell::term* shell::driver::mk_func(const unsigned op, const void *expr){
    toTerm(expr, t1);
    return new term_func(op, t1);
}

shell::term* shell::driver::mk_func(const unsigned op, const void *expr1, const void *expr2){
    toTerm(expr1, term1);
    toTerm(expr2, term2);
    return new term_func(op, term1, term2);
}

shell::fmla* shell::driver::mk_fmla_eq(const unsigned op, const void *lhs, const void *rhs){
    toTerm(lhs, term1);
    toTerm(rhs, term2);
    return new fmla_eq(op, term1, term2);
}

shell::fmla* shell::driver::mk_fmla_cnct(const unsigned op, const void *lhs, const void *rhs){
    toFmla(lhs, fmla1);
    toFmla(rhs, fmla2);
    return new fmla_cnct(op, fmla1, fmla2);
}

shell::fmla* shell::driver::mk_fmla_neg(const void *arg){
    toFmla(arg,res);
    return new fmla_neg(res);
}

shell::fmla* shell::driver::mk_fmla_quant(const unsigned op, const std::string &name, const void *formula){
    toFmla(formula, fmla1);
    toTermVar(shell::driver::mk_var(name), var);
    return new fmla_quant(op, var, fmla1);
}

void shell::driver::set_fmla(const std::string &name){
    fmla_env.insert(name, NULL);
}

void shell::driver::set_fmla(const std::string &name, const void *formula){
    toFmla(formula, fmla1);
    fmla_env.insert(name, fmla1);
}

void shell::driver::eval_fmla(const std::string &name){
    const fmla* formula;
    try{
        formula = fmla_env.lookup(name);
    } catch(const std::exception& ex){
        std::cerr << ex.what() << "\n";
    }
    if (formula == NULL){
        std::cerr << "Error: formula " << name << " was not found.\n";
    } else{
        print_fmla(formula);
    }
}

void shell::driver::error(const std::string &err){
    std::cerr << "Error: " << err << "\n";
}