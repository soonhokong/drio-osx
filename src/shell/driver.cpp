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

#define toTerm(x,y) const term* y =  static_cast<const term*>(x)
#define toTermVar(x,y) term_var* y =  static_cast<term_var*>(x)

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

void shell::driver::print(const void* expr){
    toTerm(expr,res);
    try{
        std::cout << res->val()  << "\n";
    } catch(const std::exception& ex){
        std::cerr << ex.what() << "\n";
    }
}

void shell::driver::print_env(){
    for (auto i = var_env.begin(); i != var_env.end(); ++i){
        if (i->first != ""){
            std::cout << i->first << ":" << i->second->name() << " ~ " << i->second->val() << "\n";
        }
    }
}

void shell::driver::set_var(const std::string &name, void *expr){
    toTermVar(expr,res);
    unsigned type;
    try{
        type = var_env.lookup(name)->type();

    } catch(const std::exception& ex){
        type = Real;
    }
    res->set_type(type);
    var_env.insert(name, res);
}

shell::term* shell::driver::mk_const(const double num, const unsigned type){
    return new term_const(num, type);
}

shell::term* shell::driver::mk_var(const std::string &name, const unsigned type){
    term_var * res = new term_var(name, type);
    var_env.insert(name,res);
    return new term_var(name, type);
}

//Single arg constructor for possibly inheriting a type.
shell::term* shell::driver::mk_var(const std::string &name){
    unsigned type;
    try{
        type = var_env.lookup(name)->type();
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
    toTerm(expr1,res1);
    toTerm(expr2,res2);
    return new term_func(op, res1, res2);
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
