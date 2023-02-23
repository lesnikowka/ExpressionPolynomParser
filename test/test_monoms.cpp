#include <gtest.h>
#include"monom.h"

TEST(Monoms, can_create_empty) {
	ASSERT_NO_THROW(Monom());
}
TEST(Monoms, can_create_with_empty_string) {
	ASSERT_NO_THROW(Monom(""));
}
TEST(Monoms, can_create_with_non_empty_string) {
	ASSERT_NO_THROW(Monom("-1.74xyzx^5xz^0y"));
}
TEST(Monoms, coefficient_identify_correctly) {
	Monom m("-1.74xyzx^5xz^0y");
	EXPECT_EQ(m.getCoef(),-1.74);
}
TEST(Monoms, coefficient_identify_correctly_EMPTY_MONOM) {
	Monom m;
	EXPECT_EQ(m.getCoef(), 0);
}
TEST(Monoms, coefficient_identify_correctly_MONOM_WITH_EMPTY_STRING) {
	Monom m("");
	EXPECT_EQ(m.getCoef(), 0);
}
TEST(Monoms, degrees_identify_correctly_ONE_LETTER_MEETS_ONCE) {
	Monom m("x^1*y^1z^1");
	for(int i=0;i<m.getDegrees().size();i++)
		EXPECT_EQ(m.getDegrees()[i],1);
}
TEST(Monoms, degrees_identify_correctly_EMPTY_MONOM) {
	Monom m;
	for (int i = 0; i < m.getDegrees().size(); i++)
		EXPECT_EQ(m.getDegrees()[i], 0);
}
TEST(Monoms, degrees_identify_correctly_MONOM_WITH_EMPTY_STRING) {
	Monom m("");
	for (int i = 0; i < m.getDegrees().size(); i++)
		EXPECT_EQ(m.getDegrees()[i], 0);
}
TEST(Monoms, degrees_identify_correctly_LETTERS_PLACE_CHAOTIC_AND_MEETS_MORE_THAN_ONCE) {
	Monom m("xzxyx^10z");
	std::vector<int> degrees = {12,1,2};
	for (int i = 0; i < m.getDegrees().size(); i++)
		EXPECT_EQ(m.getDegrees()[i], degrees[i]);
}
TEST(Monoms, isSimilar_ON_SIMILAR_MONOMS) {
	EXPECT_EQ(Monom("2xyz").isSimilar(Monom("xyz")), 1);
}
TEST(Monoms, isSimilar_ON_NON_SIMILAR_MONOMS) {
	EXPECT_EQ(Monom("2xyz").isSimilar(Monom("xy^2z")), 0);
}
TEST(Monoms, equality_operator_ON_SIMILAR_MONOMS) {
	EXPECT_EQ(Monom("2xy^2zx^0")==(Monom("2xy^2z")), 1);
}
TEST(Monoms, equality_operator_ON_NON_SIMILAR_MONOMS) {
	EXPECT_EQ(Monom("2xy^2zx^0") == (Monom("1xy^2z")), 0);
}

TEST(Monoms, comparison_operator_greater_ON_SIMILAR_MONOMS) {
	EXPECT_EQ(Monom("2xyz") > (Monom("xyz")), 1);
}
TEST(Monoms, comparison_operator_greater_ON_NON_SIMILAR_MONOMS) {
	EXPECT_EQ(Monom("2x^2yz") > (Monom("xy^2z^3")), 0);
}

TEST(Monoms, comparison_operator_lower_ON_SIMILAR_MONOMS) {
	EXPECT_EQ(Monom("2xyz") < (Monom("xyz")), 0);
}
TEST(Monoms, comparison_operator_lower_ON_NON_SIMILAR_MONOMS) {
	EXPECT_EQ(Monom("2x^2yz") < (Monom("xy^2z^3")), 1);
}

TEST(Monoms, integral_work_correctly_on_empty_monom) {
	Monom m;
	m.integral('y').integral('y');
	EXPECT_EQ(m.getDegrees()[1],1);
	EXPECT_EQ(m.getCoef(), 2);

}
