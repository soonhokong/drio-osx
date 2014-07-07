/* Author: Jichao Sun <jichaos@andrew.cmu.edu> 
 * Copyright 2014 Jichao Sun
 */

#include <iostream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <utility>
#include "shell/driver.h"

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

/* var_env  -> unordered map for variables
   form_env -> unordered map for formulas
   temp_env -> unordered map for temporary variables */
dreal::scoped_env var_env;
dreal::scoped_env form_env;
dreal::scoped_env temp_env;

void shell::driver::print(const double num){
    std::cout << num  << "\n";
}

void shell::driver::print(const bool bval){
    std::cout << (bval == 0 ? "false" : "true") << "\n";
}

void shell::driver::print_var(const std::string &var){
    std::cout << var << " = " << shell::driver::get_var(var);
}

void shell::driver::print_env(){
    for (auto i = var_env.begin(); i != var_env.end(); ++i){
        if (i->first != ""){
            std::cout << i->first << ":" << i->second.first << " ~ " << i->second.second << "\n";
        }
    }
}

void shell::driver::update_var(const std::string &var, const std::string &type, const double num){
    var_env.insert(var, make_pair(type, num));
}

double shell::driver::get_var(const std::string &var){
    std::pair<std::string, double > res;
    try{
        res = temp_env.lookup(var);
    }
    catch (int err){
       try{
            res = var_env.lookup(var);
        }
        catch (int err){
            std::cout << "Variable " << var << " is undefined, defaulting to 0\n";
            return 0;
        }
    }
    
    if (res.first != "real")
        return static_cast<int>(res.second + 0.5);
    else
        return res.second;
}

/* Updates formulas */
void shell::driver::update_form(const std::string &name, const std::string &formula){
    std::cout << "Updating formula " << name << " as " << formula << "\n";
    form_env.insert(name, make_pair(formula, 0));
}

/* Assigns temporary variable for formula evaluation */
void shell::driver::update_temp(const std::string &name, const std::string &type, const double num){
    temp_env.insert(name,make_pair(type, num));
}

/* Formula evalutation e.g. formula.eval */
void shell::driver::eval(const std::string &name){
    std::pair<std::string, double > res;
    std::string formula;
    try{
        res = form_env.lookup(name);
    }
    catch (int e){
        std::cout << "Formula " << name << " is undefined.\n";
        temp_env.clear();
        return;
    }
    if (res.first == ""){
        std::cout << "Formula " << name << " is empty.\n";
    }
    else{
        formula += res.first;
        formula += '\n';
        std::istringstream form_stream(formula);
        scanner->yypush_buffer_state(scanner->yy_create_buffer(&form_stream,sizeof(formula)));
        parser->parse();
        scanner->yypop_buffer_state();
    }
    temp_env.clear();
}
