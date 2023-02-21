#include <gtest.h>

#include"unordered-table.h"
#include<string>

int main(int argc, char **argv)
{
	UnorderedTable<int, std::string> test;
	test.emplace(10,"a");
	test.emplace(12, "b");
	test.emplace(17, "a");

	test.emplace(3,"c");

	std::cout << test;
	
	std::cout << "delete\n";
	test.erase(12);
	std::cout << test;
	//::testing::InitGoogleTest(&argc, argv);
	//return RUN_ALL_TESTS();
	return 0;
}
