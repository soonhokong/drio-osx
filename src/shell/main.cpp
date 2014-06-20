/* Author: Jichao Sun <jichaos@andrew.cmu.edu> */

#include <iostream>
#include <cstdlib>
#include "sh_driver.hpp"

int main(int argc, char const *argv[])
{
	SH::SH_Driver driver;
	while(1){
		driver.parse();
	}
	return 0;
}
