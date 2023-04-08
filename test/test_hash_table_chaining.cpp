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
		EXPECT_EQ(it.first,v[it.first].first);
		EXPECT_EQ(it.second, v[it.first].second);
		i++;
	}
}

class HashTable_Chaining_F :public ::testing::Test {
protected:
	HashTableC<int, int> ht;
public:
	HashTable_Chaining_F() {
		for (int i = -100; i < 100; i++)
			ht.emplace(i, i);
	}
};

TEST_F(HashTable_Chaining_F, find_work) {
	EXPECT_NO_THROW(ht.find(2));
	EXPECT_NO_THROW(ht.find(-105));
}

TEST_F(HashTable_Chaining_F, find_work_correctly) {
	for (int i = -100; i < 100; i++) {
		EXPECT_EQ((*(ht.find(i))).first, i);
		EXPECT_EQ((*(ht.find(i))).second,i);
	}
	for (int i = 101; i < 111; i++) {
		EXPECT_EQ(ht.find(i),ht.end());
	}
}

TEST_F(HashTable_Chaining_F, erase_work_with_existing_key) {
	ASSERT_NO_THROW(ht.erase(0));
}
TEST_F(HashTable_Chaining_F, erase_work_with_non_existing_key) {
	ASSERT_ANY_THROW(ht.erase(1000));
}
TEST_F(HashTable_Chaining_F, erase_work_correctly_with_existing_key) {
	ht.erase(0);
	EXPECT_EQ(ht.find(0),ht.end());
}
TEST_F(HashTable_Chaining_F, cant_erase_empty_table) {
	for(int i=-100;i<100;i++)
		EXPECT_NO_THROW(ht.erase(i));
	for (int i = -110; i < 110; i++)
		EXPECT_ANY_THROW(ht.erase(i));
}