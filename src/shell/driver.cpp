/* Author: Jichao Sun <jichaos@andrew.cmu.edu>
 * Copyright 2014 Jichao Sun
 */

#include <iostream>
#include <sstream>
#include <unordered_map>
#include <string>
#include <utility>
#include "shell/driver.h"
#include "types/formula/term.h"
#include "types/formula/function.h"
#include "types/formula/formula.h"
#include "types/formula/atom.h"
#include "types/formula/connective.h"
#include "types/formula/quantifier.h"

using std::cout;
using std::cin;
using std::cerr;
using std::exception;
using std::make_pair;
using std::string;

/* var_env  -> unordered map for variables
   fmla_env -> unordered map for formulas */

shell::driver::~driver(){
    delete scanner;
    scanner = nullptr;
    delete parser;
    parser = nullptr;
}

void shell::driver::parse(){
    delete scanner;
    scanner = new shell::scanner(&cin);
    delete parser;
    parser = new shell::parser(*scanner, *this);

    if (parser->parse() != 0){
        cerr << "Parse failed \n";
    }
}

void shell::driver::print_exp(const term t){
    try{
        cout << t.val()  << "\n";
    } catch(const exception& ex){
        cerr << ex.what() << "\n";
    }
}

void shell::driver::print_fmla(const fmla f){
    try{
        cout << (f.val() ? "true" : "false") << "\n";
    } catch(const exception& ex){
        cerr << ex.what() << "\n";
    }
}

void shell::driver::eval_fmla(const string &name){
    try{
        fmla formula = shell::fmla_lookup(name);
        if (formula.is_empty()){
            cerr << "Error: formula " << name << " was not found.\n";
        } else {
            print_fmla(formula);
        }
    } catch(const exception& ex){
        cerr << ex.what() << "\n";
    }
}


void shell::driver::error(const string &err){
    cerr << "Error: " << err << "\n";
}
