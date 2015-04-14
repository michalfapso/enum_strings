#include "a.h"
#include <iostream>

ENUM_DEFINITION(Animals);

A::A(Animals a) : mVal(a) {
	std::cout << "A("<<a<<")" << std::endl;
}

