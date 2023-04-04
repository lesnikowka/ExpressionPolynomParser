#include <iostream>
#include"Red-Black-trees.h"
#include"monom.h"
#include"hash-table(chaining).h"
#include"expression.h"
#include"unordered-table.h"
#include"ordered-table.h"
#include"hash-table(open-adressing).h"
#include"AVL-tree.h"

#include<ctime>
//x^3+3x^2z+3z^2x+z^3
//x^2+2xz+z^2

int main()
{

	
	RBTree<int,int> t,t2;
	std::vector<int> v = {7,5,10,2,8,6,11,1};

	for (auto it : v)
		t.emplace(it,it);
	std::cout << t << "\n\n";
	//std::vector<int> v = {1,2,5,6,7,8,10,11};
	

	for (auto i:v) {
		if (i == 5)
		i=5;
		t.erase(i);
		std::cout << "Deleted:" << i << "\n" << "Propertys:" << t.property_ALL(t.begin()) << "\n\n";
		std::cout << t<<"\n\n";
	}
	
	return 0;
}
