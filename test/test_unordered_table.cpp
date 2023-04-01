#include "gtest/gtest.h"

#include"unordered-table.h"


TEST(UnorderedTable, can_emplace) {
	UnorderedTable<int,int> ut;
	for(int i=-10;i<10;i++)
	ASSERT_NO_THROW(ut.emplace(i,i));
}

TEST(UnorderedTable, can_insert) {
	UnorderedTable<int, int> ut;
	for (int i = -10; i < 10; i++)
		ASSERT_NO_THROW(ut.insert({ i, i }));
}

TEST(UnorderedTable, can_find_existing_elem) {
	UnorderedTable<int, int> ut;
	for (int i = -10; i < 10; i++)
		ut.insert({ i, i });
	for (int i = -10; i < 10; i++)
		ASSERT_NO_THROW(ut.find(i));
}

TEST(UnorderedTable, can_find_non_existing_elem) {
	UnorderedTable<int, int> ut;
	ut.insert({1,1});
	for (int i = 11; i < 20; i++)
		ASSERT_NO_THROW(ut.find(i));
}

TEST(UnorderedTable, find_work_correctly) {
	UnorderedTable<int, int> ut;
	for (int i = -10; i < 10; i++)
		ut.insert({ i, 10-i });
	for (int i = -10; i < 10; i++) {
		EXPECT_EQ((*(ut.find(i))).first, i);
		EXPECT_EQ((*(ut.find(i))).second, 10-i);

	}
	for (int i = 11; i < 20; i++)
		EXPECT_EQ(ut.find(i), ut.end());
}

TEST(UnorderedTable, can_erase_existing_elem) {
	UnorderedTable<int, int> ut;
	for (int i = 0; i < 10; i++) {
		ut.emplace(i,i);
	}
	for(int i=3;i<5;i++)
	ASSERT_NO_THROW(ut.erase(i));
}
TEST(UnorderedTable, throw_when_erase_non_existing_elem) {
	UnorderedTable<int, int> ut;
	for (int i = 0; i < 10; i++) {
		ut.emplace(i, i);
	}
	for (int i = 13; i < 15; i++)
		ASSERT_ANY_THROW(ut.erase(i));
}
TEST(UnorderedTable, insert_do_nothing_when_keys_are_equal) {
	UnorderedTable<int, int> ut;
	for (int i = 0; i < 10; i++) {
		ut.insert({ 1,1 });
	}
	EXPECT_EQ(ut.size(), 1);
}
TEST(UnorderedTable, emplace_do_nothing_when_keys_are_equal) {
	UnorderedTable<int, int> ut;
	for (int i = 0; i < 10; i++) {
		ut.emplace(1,1);
	}
	EXPECT_EQ(ut.size(), 1);
}
