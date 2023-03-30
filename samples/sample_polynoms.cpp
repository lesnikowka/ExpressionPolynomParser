#include <iostream>
#include"Red-Black-trees.h"
#include"monom.h"
#include"hash-table(chaining).h"
#include"expression.h"
int main()
{
	Expression e;
	e.addExp("a=xyz");
	e.addExp("a");
	e.addExp("b=xyz");
	e.addExp("b");
	e.addExp("b=2xyz");
	e.addExp("b+a");
	std::cout << e;

	return 0;
}
