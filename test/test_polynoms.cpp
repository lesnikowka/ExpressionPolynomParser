#include "gtest/gtest.h"
#include "polynom.h"
#include<iostream>

TEST(Polynom, can_create_empty_polynom) {
	ASSERT_NO_THROW(Polynom m);
}

TEST(Polynom, can_create_not_empty_polynom) {
	ASSERT_NO_THROW(Polynom m("xy+z"));
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

	//std::cout << "TEST: " << p << std::endl;

	p = p + p2;

	EXPECT_EQ(p, p3);
}


TEST(Polynom, can_sub_polynom_1){
	Polynom p("-1.3x^2y-z+xzy"), p2("1.3yx^2-3z-2xzy-x"), p3("-2.6x^2y+2z+3xzy+x");

	p -= p2;

	//std::cout << p;
	
	//std::cout << "monom test cout " << Monom("-2.6x^2y");


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

//TEST(Polynom, ){}
//TEST(Polynom, ){}
//TEST(Polynom, ){}
//TEST(Polynom, ){}
//TEST(Polynom, ){}
//TEST(Polynom, ){}
//TEST(Polynom, ){}