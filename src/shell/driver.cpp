/* Author: Jichao Sun <jichaos@andrew.cmu.edu> 
 * Copyright 2014 Jichao Sun
 */

#include <iostream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <utility>
#include "shell/driver.h"
#include "shell/scoped_env.h"
#include "types/formula/term.h"
#include "types/formula/function.h"
#include "types/formula/connective.h"

#define toTerm(x,y) const term* y =  static_cast<const term*>(x)
#define toTermVar(x,y) term_var* y =  static_cast<term_var*>(x)

#define toFmla(x,y) const fmla* y =  static_cast<const fmla*>(x)

/* var_env  -> unordered map for variables
   fmla_env -> unordered map for formulas
   temp_env -> unordered map for temporary variables */
dreal::scoped_env var_env;
dreal::scoped_env fmla_env;
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
    double num = res->val();

    //Retrieving type if already delcared
    term_type type;
    try{
        type = var_env.lookup(name).first;
    } catch(const std::exception& ex){
        type = Real;
    }
    
    try {
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
    toTerm(expr,t1);
    return new term_func(op, t1);
}

shell::term* shell::driver::mk_func(const unsigned op, const void *expr1, const void *expr2){
    toTerm(expr1,term1);
    toTerm(expr2,term2);
    return new term_func(op, term1, term2);
}

shell::fmla* shell::driver::mk_fmla_eq(const unsigned op, const void *lhs, const void *rhs){
    toTerm(lhs,term1);
    toTerm(rhs,term2);
    return new fmla_eq(op, term1, term2);
}

shell::fmla* shell::driver::mk_fmla_cnct(const unsigned op, const void *lhs, const void *rhs){
    toFmla(lhs,fmla1);
    toFmla(rhs,fmla2);
    return new fmla_cnct(op, fmla1, fmla2);
}

shell::fmla* shell::driver::mk_fmla_neg(const void *arg){
    toFmla(arg,res);
    return new fmla_neg(res);
}

// /* Updates formulas */
// void shell::driver::update_form(const std::string &name, const std::string &formula){
//     std::cout << "Updating formula " << name << " as " << formula << "\n";
//     fmla_env.insert(name, make_pair(formula, 0));
// }

// /* Assigns temporary variable for formula evaluation */
// void shell::driver::update_temp(const std::string &name, const std::string &type, const double num){
//     temp_env.insert(name,make_pair(type, num));
// }

// /* Formula evalutation e.g. formula.eval */
// void shell::driver::eval(const std::string &name){
//     std::pair<std::string, double > res;
//     std::string formula;
//     try{
//         res = fmla_env.lookup(name);
//     }
//     catch (int e){
//         std::cout << "Formula " << name << " is undefined.\n";
//         temp_env.clear();
//         return;
//     }
//     if (res.first == ""){
//         std::cout << "Formula " << name << " is empty.\n";
//     }
//     else{
//         formula += res.first;
//         formula += '\n';
//         std::istringstream input(formula);
//         scanner->yypush_buffer_state(scanner->yy_create_buffer(&input,16384));
//         parser->parse();
//         scanner->yypop_buffer_state();
//     }
//     temp_env.clear();
// }
