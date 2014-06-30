/* Author: Jichao Sun <jichaos@andrew.cmu.edu> 
 * Copyright 2014 Jichao Sun
 */

#pragma once
#include <string>
#include "shell/scanner.h"
#include "parser.tab.hh"
#include "shell/scoped_env.h"


namespace shell{

class driver{
public:
    driver() :   parser (nullptr),
                 scanner (nullptr){};

    virtual ~driver();

    void parse();

    void print(const double num);
    void print_env();
    void print_var(const std::string &var);
    void update_var(const std::string &var, const std::string &type,
                    const double num);
    double get_var(const std::string &var);

private:
    shell::parser *parser;
    shell::scanner *scanner;
};
}
