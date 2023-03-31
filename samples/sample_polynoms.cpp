#include <iostream>
#include"Red-Black-trees.h"
#include"monom.h"
#include"hash-table(chaining).h"
#include"expression.h"
int main()
{
	RBTree<int,int> t;
	t.emplace(2,2);
	t.emplace(5,5);
	t.emplace(1, 1);
	t.emplace(7, 7);


	for (auto it : t) {
		std::cout << &it<< '\n';
	}
	
	//Expression<RBTree<std::string,Polynom>> e;
	//e.addExp("a=xyz");
	//e.addExp("a");
	//e.addExp("b=xyz");
	//e.addExp("b");
	//e.addExp("b=2xyz");
	//e.addExp("b+a");
	//std::cout << e;

	return 0;
}
