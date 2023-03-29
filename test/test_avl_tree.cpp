#include "gtest/gtest.h"
#include "AVL-tree.h"
#include <vector>


class AVL_fixture : public testing::Test{
protected:
	AVLTree<int, int> t;
};

TEST_F(AVL_fixture, can_insert_in_empty_avl_tree) {
	t.insert({ 1,1 });

	
}