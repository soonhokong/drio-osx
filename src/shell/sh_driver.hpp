/* Author: Jichao Sun <jichaos@andrew.cmu.edu> */

#ifndef __SHDRIVER_HPP__
#define __SHDRIVER_HPP__ 1
 
#include <string>
#include "sh_scanner.hpp"
#include "sh_parser.tab.hh"
#include "scoped_env.h"


namespace SH{

class SH_Driver{
public:
	SH_Driver() : 	parser (nullptr),
					scanner (nullptr){};

	virtual ~SH_Driver();

	void parse();

	void print(const double num);
	void print_env();
	void print_var(const std::string &var);
	void update_var(const std::string &var, const double num);
	double get_var(const std::string &var);

private:
	SH::SH_Parser *parser;
	SH::SH_Scanner *scanner;
};
}

#endif
