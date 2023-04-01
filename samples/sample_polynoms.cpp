#include <iostream>
#include"Red-Black-trees.h"
#include"monom.h"
#include"hash-table(chaining).h"
#include"expression.h"
#include"unordered-table.h"
#include"ordered-table.h"
#include"hash-table(open-adressing).h"
#include"AVL-tree.h"
int main()
{
	RBTree<std::string, Polynom> t;
	t.emplace("a",Polynom("x"));
	//t.emplace("b",Polynom("y"));
	t.erase("a");
	for (auto it : t) {
		std::cout << &it;
	}
	//Expression<RBTree<std::string, Polynom>> a;
	//a.addExp("a===2");
	//a.addExp("a");
	return 0;
}
