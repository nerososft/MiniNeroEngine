
#include "Errors.h"
#include <iostream>
namespace NeroEngine {
	void fatalError(std::string errorString) {
		std::cout << "fatalError:" << errorString << std::endl;
		std::cout << "Enter anykey to quit...";
		int tmp;
		std::cin >> tmp;
		exit(0);
	}

}