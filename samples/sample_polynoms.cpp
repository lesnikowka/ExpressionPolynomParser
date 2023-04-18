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
	RBTree<int, int> t;
	t.emplace(1, 1);
	t.emplace(2, 2);
	std::cout << t;
	/*
	RBTree<int, int> t;
	std::vector<int> v;
	int size = 10;
	for (int i = 0; i < size; i++) {
		t.emplace(i, i);
	}
	std::cout << t <<"\n";
	bool flag = false;
	for (int i = size-1; i >=0; i--) {

		t.erase(i);
		std::cout << "Deleted:" << i << '\n';
		std::cout << "Propertys:" << ((t.property_ALL(t.begin())) ? "execut" : "non-execute") << '\n';
		//std::cout << t<<"\n\n";

	}
	*/
	
	/*
	RBTree<int,int> t,t2;
	std::vector<int> v = {7,5,10,2,8,6,11,1};

	for (auto it : v)
		t.emplace(it,it);
	std::cout << t << "\n\n";
	//std::vector<int> v = {1,2,5,6,7,8,10,11};
	

	for (auto i:v) {
		if (i == 6)
		i=6;
		t.erase(i);
		std::cout << "Deleted:" << i << "\n" << "Propertys:" << t.property_ALL(t.begin()) << "\n\n";
		std::cout << t<<"\n\n";
	}
	*/
	return 0;
}
