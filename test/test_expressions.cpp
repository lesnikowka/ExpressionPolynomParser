#include "gtest/gtest.h"
#include "expression.h"


#include"../containers/Red-Black-trees.h"
#include"../containers/AVL-tree.h"
#include"../containers/hash-table(chaining).h"
#include"../containers/hash-table(open-adressing).h"
#include"../containers/ordered-table.h"
#include"../containers/unordered-table.h"

#include<iostream>

TEST(Expression, can_sum_2_polynoms) {
	Expression<RBTree<std::string,Polynom>> a;
	Polynom p("2xyz");
	a.addExp("tmp1=xyz");
	a.addExp("tmp2=xyz");
	a.addExp("tmp1+tmp2");
	EXPECT_EQ(p, a.getResult());
}
TEST(Expression, can_minus_2_polynoms) {
		Expression<RBTree<std::string,Polynom>> a;
	Polynom p("0");
	a.addExp("tmp1=xyz");
	a.addExp("tmp2=xyz");
	a.addExp("tmp1-tmp2");
	EXPECT_EQ(p, a.getResult());
}
TEST(Expression, can_multiple_2_polynoms) {
		Expression<RBTree<std::string,Polynom>> a;
	Polynom p("x^2y^2z^2");
	a.addExp("tmp1=xyz");
	a.addExp("tmp2=xyz");
	a.addExp("tmp1*tmp2");
	EXPECT_EQ(p, a.getResult());
}
TEST(Expression, can_devide_2_polynoms) {
		Expression<RBTree<std::string,Polynom>> a;
	Polynom p("1");
	a.addExp("tmp1=xyz");
	a.addExp("tmp2=xyz");
	a.addExp("tmp1/tmp2");
	EXPECT_EQ(p, a.getResult());
}
TEST(Expression, exception_when_polynoms_cant_be_divided) {
		Expression<RBTree<std::string,Polynom>> a;
	a.addExp("tmp1=xyz");
	a.addExp("tmp2=xyz^2");
	ASSERT_ANY_THROW(
		a.addExp("tmp1/tmp2");
	);
}
