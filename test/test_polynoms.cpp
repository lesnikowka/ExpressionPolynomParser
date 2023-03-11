
#include "gtest/gtest.h"
#include "polynom.h"
#include <sstream>

class PolynomFixture : public ::testing::Test{
public:
	Polynom p1, p2;
};

TEST(Polynom, can_create_empty_polynom) {
	ASSERT_NO_THROW(Polynom m);
}
TEST(Polynom, can_create_not_empty_polynom) {
	ASSERT_NO_THROW(Polynom m("xy+z"));
}
TEST_F(PolynomFixture, can_copy_polynom) {
	Polynom p3("x+y+z");
	
	Polynom p4 = p3;

	EXPECT_EQ(p3, p4);
}
TEST_F(PolynomFixture, can_assign_polynom) {
	Polynom p3("x+y+z");

	p1 = p3;

	EXPECT_EQ(p1, p3);
}
TEST_F(PolynomFixture, can_calculate_polynom) {
	Polynom p3("2xy+xz");

	EXPECT_EQ(p3.calculate({ 1,2,3 }), 7);
}

