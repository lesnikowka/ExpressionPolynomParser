#include "gtest/gtest.h"

#include"Red-Black-trees.h"

TEST(RBTree, can_emplace) {
	RBTree<int, int> t;
	ASSERT_NO_THROW(t.emplace(2,2));
}
TEST(RBTree, can_emplace_few_times) {
	RBTree<int, int> t;
	for(int i=0;i<10;i++)
	ASSERT_NO_THROW(t.emplace(i, i));
}
TEST(RBTree, emplace_work_correctly) {
	RBTree<int, int> t;
	t.emplace(1, 2);
	EXPECT_EQ((*t.find(1)).first, 1);
	EXPECT_EQ((*t.find(1)).second, 2);
}

TEST(RBTree, find_for_existing_key_work) {
	RBTree<int, int> t;
	t.emplace(1, 1);
	ASSERT_NO_THROW(t.find(1));
}
TEST(RBTree, find_for_non_existing_key_work) {
	RBTree<int, int> t;
	t.emplace(1, 1);
	ASSERT_NO_THROW(t.find(10));
}
TEST(RBTree, find_for_existing_key_work_correctly) {
	RBTree<int, int> t;
	t.emplace(1, 2);
	EXPECT_EQ((*t.find(1)).first,1);
	EXPECT_EQ((*t.find(1)).second,2);
}
TEST(RBTree, find_for_non_existing_key_work_correctly) {
	RBTree<int, int> t;
	t.emplace(1, 1);
	EXPECT_EQ(t.find(10),t.end());
}

TEST(RBTree, emplace_the_same_key_few_times_work_correctly) {
	RBTree<int, int> t;
	t.emplace(2, 3);
	t.emplace(2, 2);
	EXPECT_EQ(t.size(),1);
	EXPECT_EQ((*t.find(2)).second,3 );
}
TEST(RBTree, emplace_different_keys_work_correctly) {
	RBTree<int, int> t;
	for (int i = 0; i < 10; i++) {
		t.emplace(i,10-i);
	}
	EXPECT_EQ(t.size(),10);
	for (int i = 0; i < 10; i++) {
		EXPECT_EQ((*t.find(i)).first,i);
		EXPECT_EQ((*t.find(i)).second,10-i);
	}
}

TEST(RBTree, erase_work_with_existing_key) {
	RBTree<int, int> t;
	t.emplace(1, 1);
	ASSERT_NO_THROW(t.erase(1));
}
TEST(RBTree, erase_throw_with_non_existing_key) {
	RBTree<int, int> t;
	t.emplace(10, 1);
	ASSERT_ANY_THROW(t.erase(1));
}
TEST(RBTree, erase_ROOT_work_with_existing_key_correctly) {
	RBTree<int, int> t;
	t.emplace(1, 1);
	t.erase(1);
	EXPECT_EQ(t.find(1),t.end());
}
TEST(RBTree, erase_LEAF_work_with_existing_key_correctly) {
	RBTree<int, int> t;
	t.emplace(1, 1);
	t.emplace(2, 1);
	t.erase(2);
	EXPECT_EQ(t.find(2), t.end());
}
TEST(RBTree, erase_NODE_work_with_existing_key_correctly) {
	RBTree<int, int> t;
	t.emplace(1, 1);
	t.emplace(2, 1);
	t.emplace(3, 1);
	t.emplace(4, 1);
	t.emplace(5, 1);

	t.erase(4);
	EXPECT_EQ(t.find(4), t.end());
}

class F_RBTree :public ::testing::Test {
public:
	std::vector<RBTree<int, int>>v;
	size_t size;
	F_RBTree() {
		size = 6;
		v.resize(size);
	}
	void insert(int key) {
		for (int i = 0; i < size; i++)
			v[i].emplace(i, i);
	}
	void erase(int key) {
		for (int i = 0; i < size; i++)
			v[i].erase(i);
	}
};

TEST_F(F_RBTree, property_BLACK_HEIGHT_is_executed) {
	
}


