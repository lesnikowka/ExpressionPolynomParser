#include "gtest/gtest.h"
#include "polynom.h"
#include<iostream>

TEST(Polynom, can_create_empty_polynom) {
	ASSERT_NO_THROW(Polynom m);
}

TEST(Polynom, can_create_not_empty_polynom) {
	ASSERT_NO_THROW(Polynom m("xy+z"));
}

TEST(Polynom, comparison_operator_is_correct_on_equal_polynoms) {
	Polynom p("x+y+z"), p2("x+y+z");

	EXPECT_TRUE(p == p2);
}

TEST(Polynom, comparison_operator_is_correct_on_unequal_polynoms) {
	Polynom p("x+y+z"), p2("x+y^2+z");

	EXPECT_TRUE(p != p2);
}

TEST(Polynom, can_copy_polynom) {
	Polynom p("x+y+z");
	
	Polynom p2 = p;

	EXPECT_EQ(p, p2);
}

TEST(Polynom, can_assign_polynom) {
	Polynom p("x+y+z"), p2;

	p2 = p;

	EXPECT_EQ(p, p2);
}

TEST(Polynom, can_calculate_polynom) {
	Polynom p("2xy+xz");

	EXPECT_EQ(p.calculate({ 1,2,3 }), 7);
}

TEST(Polynom, can_multiply_polynom_1) {
	Polynom p("-1.3x^2y-z+xzy"), p2("0.65x^2y+0.5z-0.5xzy");

	p *= -0.5;

	EXPECT_EQ(p, p2);
}

TEST(Polynom, can_multiply_polynom_2) {
	Polynom p("-1.3x^2y-z+xzy"), p2("0.65x^2y+0.5z-0.5xzy");

	p = p * ( -0.5 );

	EXPECT_EQ(p, p2);
}

TEST(Polynom, can_add_polynom_1){
	Polynom p("-1.3x^2y-z+xzy"), p2("1.3yx^2-3z-2xzy-x"), p3("-x-4z-xzy");

	p += p2;
	
	EXPECT_EQ(p, p3);
}

TEST(Polynom, can_add_polynom_2) {
	Polynom p("-1.3x^2y-z+xzy"), p2("1.3yx^2-3z-2xzy-x"), p3("-x-4z-xzy");

	p = p + p2;

	EXPECT_EQ(p, p3);
}


TEST(Polynom, can_sub_polynom_1){
	Polynom p("-1.3x^2y-z+xzy"), p2("1.3yx^2-3z-2xzy-x"), p3("-2.6x^2y+2z+3xzy+x");

	p -= p2;

	EXPECT_EQ(p, p3);
}


TEST(Polynom, can_sub_polynom_2){
	Polynom p("-1.3x^2y-z+xzy"), p2("1.3yx^2-3z-2xzy-x"), p3("-2.6x^2y+2z+3xzy+x");

	p = p - p2;

	EXPECT_EQ(p, p3);
}
TEST(Polynom, can_multiply_polynoms_1){
	Polynom p("x+y-z"), p2("xy-z^2"), p3("x^2y+xy^2-xyz-xz^2-z^2y+z^3");

	p *= p2;

	EXPECT_EQ(p, p3);
}

TEST(Polynom, can_multiply_polynoms_2) {
	Polynom p("x+y-z"), p2("xy-z^2"), p3("x^2y+xy^2-xyz-xz^2-z^2y+z^3");

	p = p2 * p;

	EXPECT_EQ(p, p3);
}

TEST(Polynom, can_devide_polynoms){
	Polynom p("x^3-3x^2y+3xy^2-y^3"), p2("x^2-2xy+y^2"), p3("x-y");

	p = (p / p2).first;

	EXPECT_EQ(p, p3);
}


TEST(Polynom, can_add_polynom_and_monom_1){
	Polynom p("xyz-0.01x^2+z"), p3("xyz+z");
	Monom m("0.01x^2");

	p += m;

	EXPECT_EQ(p, p3);
}

TEST(Polynom, can_add_polynom_and_monom_2) {
	Polynom p("xyz-0.01x^2+z"), p3("xyz+z");
	Monom m("0.01x^2");

	p = p + m;

	EXPECT_EQ(p, p3);
}
TEST(Polynom, can_sub_polynom_and_monom_1){
	Polynom p("xyz-0.01x^2+z"), p3("xyz-0.01x^2+z-yx^2");
	Monom m("yx^2");

	p -= m;

	EXPECT_EQ(p, p3);
}

TEST(Polynom, can_sub_polynom_and_monom_2) {
	Polynom p("xyz-0.01x^2+z"), p3("xyz-0.01x^2+z-yx^2");
	Monom m("yx^2");

	p = p - m;

	EXPECT_EQ(p, p3);
}

TEST(Polynom, can_multiply_polynom_and_monom_1){
	Polynom p("xyz-0.01x^2+z"), p3("0.2x^2yz^2-0.002x^3z+0.2xz^2");
	Monom m("0.2xz");

	p *= m;

	EXPECT_EQ(p, p3);
}

TEST(Polynom, can_multiply_polynom_and_monom_2) {
	Polynom p("xyz-0.01x^2+z"), p3("0.2x^2yz^2-0.002x^3z+0.2xz^2");
	Monom m("0.2xz");

	p = p * m;

	EXPECT_EQ(p, p3);
}

TEST(Polynom, can_take_a_derivative){
	Polynom p("x^2yz+x+z+1"), p3("2xyz+1");

	p = p.derivative('x');

	EXPECT_EQ(p, p3);
}
TEST(Polynom, can_take_an_integral_of_empty_polynom){
	Polynom p, p3;

	p = p.integral('x');

	EXPECT_EQ(p, p3);
}

TEST(Polynom, can_take_an_integral_of_non_empty_polynom) {
	Polynom p("2x-4x^3yz"), p3("x^2-x^4yz");

	p = p.integral('x');

	EXPECT_EQ(p, p3);
}

//TEST(Polynom, ){}

//TEST(Polynom, ){}
//TEST(Polynom, ){}
//TEST(Polynom, ){}
//TEST(Polynom, ){}
//TEST(Polynom, ){}
//TEST(Polynom, ){}
//TEST(Polynom, ){}

//TEST(Polynom, ){}
//TEST(Polynom, ){}
//TEST(Polynom, ){}
//TEST(Polynom, ){}
//TEST(Polynom, ){}
//TEST(Polynom, ){}
//TEST(Polynom, ){}