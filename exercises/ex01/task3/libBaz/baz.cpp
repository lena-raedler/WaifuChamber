#include "baz.hpp"

#include <iostream>

//#include "bar.hpp"
#include "../libBar/bar.hpp"

void baz()
{
	bar();
	std::cout << "Function baz called" << std::endl;
}
