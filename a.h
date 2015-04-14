#ifndef A_H
#define A_H

#include "enum_conversions_macro.h"

ENUM_CLASS(Animals, DOG, CAT, COW);

class A {
	public:
		A(Animals a);
	private:
		Animals mVal;
};

#endif

