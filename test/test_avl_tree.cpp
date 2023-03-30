#include "gtest/gtest.h"
#include "AVL-tree.h"
#include <vector>


class AVL_fixture : public testing::Test{
protected:
	AVLTree<int, int> t;
};
