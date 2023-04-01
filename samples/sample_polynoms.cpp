#include <iostream>
#include"Red-Black-trees.h"
#include"monom.h"
#include"hash-table(chaining).h"
#include"expression.h"
#include"unordered-table.h"
#include"hash-table(open-adressing).h"
int main()
{
	HashTableC<int, int> ht;
	for(int i=0;i<9;i++)
	ht.emplace(i, i);
	ht.erase(1000);
	std::cout << ht;
	return 0;
}
