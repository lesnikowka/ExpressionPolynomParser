#include <iostream>
#include"Red-Black-trees.h"
#include"monom.h"
#include"hash-table(chaining).h"
#include"expression.h"
#include"unordered-table.h"
#include"hash-table(open-adressing).h"
int main()
{
	Monom a("2xyz");
	std::cout << a<<'\n';

	Expression<RBTree<std::string,Polynom>> e;
	e.addExp("a=xyz");
	e.addExp("a");
	e.addExp("a*2");
	std::cout << e;
	return 0;
}
