#include "gtest/gtest.h"
#include "expression.h"


#include"Red-Black-trees.h"
#include"AVL-tree.h"
#include"hash-table(chaining).h"
#include"hash-table(open-adressing).h"
#include"ordered-table.h"
#include"unordered-table.h"

#include<iostream>

template<typename T>
class Expression_Typed :public ::testing::Test {
public:
	Expression<T> n;
};

using Types = ::testing::Types<RBTree<std::string, Polynom>, AVLTree<std::string, Polynom>, UnorderedTable<std::string, Polynom>, OrderedTable<std::string, Polynom>,HashTableC<std::string, Polynom>,HashTableOpenAdressing<std::string, Polynom>>;


TYPED_TEST_SUITE(Expression_Typed, Types);


TYPED_TEST(Expression_Typed, can_create_monom) {
	auto a = this->n;
	Polynom p("xyz");
	a.addExp("a");
	a.addExp("a=xyz");
	EXPECT_EQ(p, a.getResult());
}
TYPED_TEST(Expression_Typed, can_create_polynom) {
	auto a = this->n;
	Polynom p("xyz+xz+x^2");
	a.addExp("a");
	a.addExp("a=xyz+xz+x^2");
	EXPECT_EQ(p, a.getResult());
}

TYPED_TEST(Expression_Typed, can_sum_2_polynoms) {
	auto a = this->n;
	Polynom p("2xyz");
	a.addExp("tmp1=xyz");
	a.addExp("tmp2=xyz");
	a.addExp("tmp1+tmp2");
	EXPECT_EQ(p, a.getResult());
}
TYPED_TEST(Expression_Typed, can_minus_2_polynoms) {
	auto a = this->n;

	Polynom p("0");
	a.addExp("tmp1=xyz");
	a.addExp("tmp2=xyz");
	a.addExp("tmp1-tmp2");
	EXPECT_EQ(p, a.getResult());
}
TYPED_TEST(Expression_Typed, can_multiple_2_polynoms) {
	auto a = this->n;
	Polynom p("x^2y^2z^2");
	a.addExp("tmp1=xyz");
	a.addExp("tmp2=xyz");
	a.addExp("tmp1*tmp2");
	EXPECT_EQ(p, a.getResult());
}
TYPED_TEST(Expression_Typed, can_divide_2_polynoms) {
	auto a = this->n;
	Polynom p("1");
	a.addExp("tmp1=xyz");
	a.addExp("tmp2=xyz");
	a.addExp("tmp1/tmp2");
	EXPECT_EQ(p, a.getResult());
}
TYPED_TEST(Expression_Typed, exception_when_polynoms_cant_be_divided) {
	auto a = this->n;
	a.addExp("tmp1=xyz");
	a.addExp("tmp2=xyz^2");
	ASSERT_ANY_THROW(a.addExp("tmp1/tmp2"));
}


