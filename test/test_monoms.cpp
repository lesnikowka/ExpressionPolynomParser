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
	EXPECT_EQ(Monom("2xyz") > (Monom("xyz")), 0);
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
	Monom m,res;
	res=m.integral('y').integral('y');
	EXPECT_EQ(res.getDegrees()[1],0);
	EXPECT_EQ(res.getCoef(), 0);

}
TEST(Monoms, integral_work_correctly_on_non_empty_monom) {
	Monom m("-6xyz"), res;
	res = m.integral('y').integral('y');
	EXPECT_EQ(res.getDegrees()[1], 3);
	EXPECT_EQ(res.getCoef(), -1);
}

TEST(Monoms, derivative_work_correctly_on_empty_monom) {
	Monom m, res;
	res = m.derivative('y').derivative('y');
	EXPECT_EQ(res.getDegrees()[1], 0);
	EXPECT_EQ(res.getCoef(), 0);

}
TEST(Monoms, derivative_work_correctly_on_non_empty_monom_DERIVATE_MORE_TIMES_THAN_DEGREE_SIZE) {
	Monom m("-6xyz"), res;
	res = m.derivative('y').derivative('y');
	EXPECT_EQ(res.getDegrees()[1], 0);
	EXPECT_EQ(res.getCoef(), 0);
}
TEST(Monoms, derivative_work_correctly_on_non_empty_monom_DERIVATE_LESS_TIMES_THAN_DEGREE_SIZE) {
	Monom m("0.2xy^5z"), res;
	res = m.derivative('y').derivative('y');
	EXPECT_EQ(res.getDegrees()[1], 3);
	EXPECT_EQ(res.getCoef(), 4);
}

TEST(Monoms, addition_operator_work_correctly) {
	Monom m1("xyz"), m2("2xyz");
	std::vector<int> deg = { 1,1,1 };
	EXPECT_EQ((m1 + m2).getCoef(), 3);
	EXPECT_EQ((m1+m2).getDegrees(),deg);
}
TEST(Monoms, addition_operator_work_correctly_NON_SIMILAR_MONOMS) {
	Monom m1("xyz"), m2("2xy^2z");
	ASSERT_ANY_THROW((m1 + m2));
}
TEST(Monoms, addition_operator_work_correctly_EMPTY_MONOMS) {
	Monom m1, m2;
	EXPECT_EQ((m1 + m2).getCoef(), 0);
	EXPECT_EQ((m1 + m2).getDegrees(), std::vector<int>({0,0,0}));
}
TEST(Monoms, multiplication_operator_work_correctly) {
	Monom m1("xyz"), m2("2xy^3z");
	std::vector<int> deg = { 2,4,2 };
	EXPECT_EQ((m1 * m2).getCoef(), 2);
	EXPECT_EQ((m1 * m2).getDegrees(), deg);
}
TEST(Monoms, multiplication_operator_work_correctly_EMPTY_MONOMS) {
	Monom m1, m2;
	EXPECT_EQ((m1 * m2).getCoef(), 0);
	EXPECT_EQ((m1 * m2).getDegrees(), std::vector<int>({ 0,0,0 }));
}

TEST(Monoms, can_correctly_calculate_monom_at_the_dot) {
	Monom m("-1.5x^3y");
	EXPECT_EQ(m.calculate({1,10,3}),-15 );
}