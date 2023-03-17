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
//TEST(Polynom, ){}
//TEST(Polynom, ){}
//TEST(Polynom, ){}
//TEST(Polynom, ){}
//TEST(Polynom, ){}
//TEST(Polynom, ){}
//TEST(Polynom, ){}
//TEST(Polynom, ){}