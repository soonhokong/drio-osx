/* Author: Jichao Sun <jichaos@andrew.cmu.edu> 
 * Copyright 2014 Jichao Sun
 */

#include <iostream>
#include <unordered_map>
#include <string>
#include "sh_driver.h"

SH::SH_Driver::~SH_Driver(){
    delete scanner;
    scanner = nullptr;
    delete parser;
    parser = nullptr;
}

void SH::SH_Driver::parse(){
    delete scanner;
    scanner = new SH::SH_Scanner();
    delete parser;
    parser = new SH::SH_Parser(*scanner, *this);

    if (parser->parse() != 0){
        std::cerr << "Parse failed \n";
    }
}


dreal::scoped_env scoped_env;

void SH::SH_Driver::print_var(const std::string &var){
    std::cout << var << " = " << SH::SH_Driver::get_var(var);
}

void SH::SH_Driver::print(const double num){
    std::cout << num  << "\n";
}

void SH::SH_Driver::print_env(){
    for (auto i = scoped_env.begin(); i != scoped_env.end(); ++i){
        if (i->first != "")
        {
            std::cout << i->first << ":" << i->second.first << " ~ " << i->second.second << "\n";
        }
    }
}

void SH::SH_Driver::update_var(const std::string &var, const std::string &type, 
                               const double num){
    scoped_env.insert(var, make_pair(type,num));
}

double SH::SH_Driver::get_var(const std::string &var){
    std::pair<std::string, double > res;
    try{
        res = scoped_env.lookup(var);
    }
    catch (int e){
        std::cout << "Variable " << var << " is undefined, defaulting to 0\n";
        return 0;
    }
    if (res.first != "real")
        return (double)(int)(res.second + 0.5);
    else 
        return res.second;
}
