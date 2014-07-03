/* Author: Jichao Sun <jichaos@andrew.cmu.edu> 
 * Copyright 2014 Jichao Sun
 */

#include <iostream>
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

dreal::scoped_env scoped_env;

void shell::driver::print_var(const std::string &var){
    std::cout << var << " = " << shell::driver::get_var(var);
}

void shell::driver::print(const double num){
    std::cout << num  << "\n";
}

void shell::driver::print_env(){
    for (auto i = scoped_env.begin(); i != scoped_env.end(); ++i){
        if (i->first != ""){
            std::cout << i->first << ":" << i->second.first << " ~ " << i->second.second << "\n";
        }
    }
}

void shell::driver::update_var(const std::string &var, const std::string &type,
                               const double num){
    scoped_env.insert(var, make_pair(type, num));
}

double shell::driver::get_var(const std::string &var){
    std::pair<std::string, double > res;
    try{
        res = scoped_env.lookup(var);
    }
    catch (int e){
        std::cout << "Variable " << var << " is undefined, defaulting to 0\n";
        return 0;
    }
    if (res.first != "real")
        return static_cast<int>(res.second + 0.5);
    else
        return res.second;
}

void shell::driver::update_form(const std::string &name, const std::string &num){
    std::cout << "Updating formula " << name << " as " << num << "\n";
}

void shell::driver::eval(const std::string &name){
    std::cout << "Evaluating formula " << name << "\n";
}
