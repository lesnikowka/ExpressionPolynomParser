#include <iostream>
#include"Red-Black-trees.h"
#include"monom.h"
#include"hash-table(chaining).h"
#include"expression.h"
#include"unordered-table.h"
#include"hash-table(open-adressing).h"
int main()
{
	//RBTree<std::string, Polynom> t;
	//t.emplace("tmp1",Polynom("xyz"));
	//t.emplace("tmp2",Polynom("xyz"));
	//std::cout<<t;
	Expression<RBTree<std::string, Polynom>> a;
	a.addExp("a===2");
	a.addExp("a");
	return 0;
}
