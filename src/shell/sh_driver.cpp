/* Author: Jichao Sun <jichaos@andrew.cmu.edu> */

#include <iostream>
#include "sh_driver.hpp"

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
	std::cout << "Printing Environment \n";
}

void SH::SH_Driver::update_var(const std::string &var, const double num){
	scoped_env.insert(var, num);
}

double SH::SH_Driver::get_var(const std::string &var){
	double res;
	try{
		res = scoped_env.lookup(var); 
	}
	catch (int e){
		std::cout << "Variable " << var << " is undefined, defaulting to 0\n";
		return 0;		
	}
	return res;
}
