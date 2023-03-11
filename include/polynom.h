#pragma once
#include"list.h"
#include"monom.h"
#include<iostream>

class Polynom {

	const std::string using_alphabet = "xyz";
	const std::string using_symb_for_degree = "^";
	const std::string using_symb_for_multiplie = "*";
	const std::string using_separator = ".";
	const std::string using_nums = "0123456789";
	const std::string using_operators = "+-*^";

	List<Monom> monoms;
	

	void sort();
	void cut();
public:

	Polynom() = default;
	Polynom(const Polynom& p) = default;
	Polynom(std::string str);

	double calculate(std::vector<double> vect);

	Polynom operator+(const Polynom& p);
	Polynom& operator+=(const Polynom& p);
	
	Polynom operator-(const Polynom& p);
	Polynom& operator-=(const Polynom& p);
	
	Polynom operator*(const Polynom& p);
	Polynom& operator*=(const Polynom& p);
	
	std::pair<Polynom,Polynom> operator/(const Polynom& p);
	
	Polynom integ(char s);
	Polynom dif(char s);


	Polynom& operator=(const Polynom & m);
	bool operator==(const Polynom& m);



	friend std::istream& operator>>(std::istream& istream, Polynom& p);
	friend std::ostream& operator<<(std::ostream& ostream, Polynom& p);
};