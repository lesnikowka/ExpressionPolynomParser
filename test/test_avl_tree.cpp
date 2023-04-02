#include "gtest/gtest.h"
#include "AVL-tree.h"
#include <vector>
#include <algorithm>

template<class A, class B>
bool is_equal(A v, B t) {
	for (auto i : v) {
		if (t.find(i.first) == t.end()) return false;
	}
	for (auto i : t) {
		if(std::find(v.begin(), v.end(), i) == v.end()) return false;
	}
	return true;
}

class AVL_fixture : public testing::Test{
protected:
	AVLTree<int, int> t;
	std::vector<std::pair<int, int>> v = { {4, 5}, {3, 7}, {10, 17}, {8, 13}, {12, 7}, {13, 14} , {1, 10} };
};

TEST_F(AVL_fixture, size_is_correct_on_empty_tree) {
	int tsize = t.size();
	EXPECT_EQ(0, t.size());
}
TEST_F(AVL_fixture, size_is_correct_in_common_case) {
	for (auto i : v) {
		t.insert(i);
	}

	EXPECT_EQ(t.size(), v.size());
}
TEST_F(AVL_fixture, size_is_correct_after_erasing) {
	t.emplace(1,1);
	t.emplace(2,2);
	t.erase(1); 
	t.erase(2);

	EXPECT_EQ(t.size(), 0);
}

TEST_F(AVL_fixture, can_insert_elements) {
	for (auto i : v) {
		t.insert(i);
	}
	
	bool equal = is_equal<std::vector<std::pair<int, int>>, AVLTree<int, int>>(v, t);
	EXPECT_TRUE(equal);
}

TEST_F(AVL_fixture, can_emplace_elements) {
	for (auto i : v) {
		t.emplace(i.first, i.second);
	}

	bool equal = is_equal<std::vector<std::pair<int, int>>, AVLTree<int, int>>(v, t);
	EXPECT_TRUE(equal);
}

TEST_F(AVL_fixture, can_erase_root) {
	for (auto i : v) {
		t.emplace(i.first, i.second);
	}

	t.erase(10);

	v.erase(std::find(v.begin(), v.end(), std::pair<int, int>(10, 17)));

	bool equal = is_equal<std::vector<std::pair<int, int>>, AVLTree<int, int>>(v, t);
	EXPECT_TRUE(equal);
}

TEST_F(AVL_fixture, can_erase_list) {
	for (auto i : v) {
		t.emplace(i.first, i.second);
	}

	t.erase(3);

	v.erase(std::find(v.begin(), v.end(), std::pair<int, int>(3, 7)));

	bool equal = is_equal<std::vector<std::pair<int, int>>, AVLTree<int, int>>(v, t);
	EXPECT_TRUE(equal);
}

TEST_F(AVL_fixture, can_erase_medium_point) {
	for (auto i : v) {
		t.emplace(i.first, i.second);
	}

	t.erase(4);
	v.erase(std::find(v.begin(), v.end(), std::pair<int, int>(4, 5)));

	for (auto i : v) {
		EXPECT_FALSE(t.find(i.first) == t.end());
	}
	for (auto i : t) {
		EXPECT_FALSE(std::find(v.begin(), v.end(), i) == v.end());
	}
	EXPECT_TRUE(true);
}

TEST_F(AVL_fixture, throw_if_erase_element_that_was_not_added) {
	for (auto i : v) {
		t.emplace(i.first, i.second);
	}

	ASSERT_ANY_THROW(t.erase(9));
}

