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
	RBTree<int, int> t1,t2,t3;
	std::vector<int> v1={7, 5, 10, 2, 8, 6, 11, 1},
	v2={ 9,8,7,6,5,4,3,2,1,0 },
		v3= { 12,10,15,8,13 };
	for (auto it : v1)t1.emplace(it, it);
	for (auto it : v2)t2.emplace(it, it);
	for (auto it : v3)t3.emplace(it, it);

	std::cout << t3<<'\n';

	for (int i = 0; i < v3.size(); i++) {
		std::cout << "deleted:" << v3[i]<<'\n';
		t3.erase(v3[i]);
		std::cout << t3<<'\n';
	}
	//for (int i = 0; i < v2.size() / 2; i++) {
	//	t2.erase(v2[i]);
	//}

	//std::cout << t1;
	//std::cout << t2.property_ALL(t2.begin());

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
