#include "gtest/gtest.h"

#include"hash-table(chaining).h"



TEST(HashTable_Chaining, can_emplace) {
	HashTableC<int, int> ht;
	ASSERT_NO_THROW(ht.emplace(1,1));
}

TEST(HashTable_Chaining, can_emplace_few_times) {
	HashTableC<int, int> ht;
	for(int i=0;i<10;i++)
	ASSERT_NO_THROW(ht.emplace(i, i));
}
TEST(HashTable_Chaining, do_nothing_when_emplace_the_same_key) {
	HashTableC<int, int> ht;
	for(int i=0;i<10;i++)
	ht.emplace(1, 1);
	EXPECT_EQ(1,ht.getSize());
}

TEST(HashTable_Chaining, emplace_work_correctly) {
	HashTableC<int, int> ht;
	std::vector<std::pair<int, int>> v = { {0,0} ,{1,1},{2,2},{3,3},{4,4},{5,5} };
	for (auto it : v)
		ht.emplace(it.first,it.second);
	int i = 0;
	for (auto it:ht) {
		EXPECT_EQ(it.key,v[it.key].first);
		EXPECT_EQ(it.elem, v[it.key].second);
		i++;
	}
}

class HashTable_Chaining :public ::testing::Test {
protected:
	HashTableC<int, int> ht;
public:
	HashTable_Chaining() {
		for (int i = -100; i < 100; i++)
			ht.emplace(i, i);
	}
};
