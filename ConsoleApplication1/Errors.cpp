<<<<<<< HEAD
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
=======
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
>>>>>>> 569357d9b33b73a7a369a00dc66de4303f7138a5
}