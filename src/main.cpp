/* Author: Jichao Sun <jichaos@andrew.cmu.edu>
 * Copyright 2014 Jichao Sun
 */

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <string>
#include "shell/driver.h"

inline void prompt(std::string const & msg) {
    std::cout << msg;
    std::cout.flush();
}

int main(){
    shell::driver driver;
    std::string line;
    while (1){
        prompt("drio # ");
        std::getline(std::cin, line);
        std::stringstream ss(line + "\n");
        driver.parse(ss);
    }
    return 0;
}
