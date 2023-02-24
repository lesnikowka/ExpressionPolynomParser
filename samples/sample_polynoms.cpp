#include <iostream>

#include"monom.h"

void main()
{
	Monom m1("-6x^3y^4z^5"),
		m2("2x^3y^4z^5");
	std::cout << (m1<=m2);
}
