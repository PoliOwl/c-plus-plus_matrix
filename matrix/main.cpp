#include <iostream>
#include "Finite.h"
#include "rational.h"
#include "matrix.h"
#include <vector>



int main()
{
	/*matrix<rational, 5> f(rational(0));
	std::cout << f;*/
	matrix<rational, 5> f =  matrix<rational, 5>::get_one();
	std::cout << f;
}

