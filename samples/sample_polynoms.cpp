#include <iostream>
#include"Red-Black-trees.h"
#include"monom.h"
int main()
{
	RBTree<int,int> t;
	t.insert(7, 7);

	t.insert(8, 8);

	t.insert(6, 6);

	t.insert(5, 5);

	//t.insert(3, 3);

	//for(int i=0;i<9;i++)
	//std::cout << i<<")"<<t.getParent(t.find(i))<<"\n";
	std::cout << t;


	//std::cout << t.U(t.find(7));
	//t.insert(2, 2);
	//t.insert(1, 1);
	


	return 0;
}
