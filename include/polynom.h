#pragma once
#include"list.h"
#include"monom.h"
#include<iostream>

class Polynom {


	List<Monom> monoms;
	

	void sort();
	void cut();
public:
	std::string using_alphabet = Monom::using_alphabet,
		using_symb_for_degree = Monom::using_symb_for_degree,
		using_symb_for_multiplie = Monom::using_symb_for_multiplie,
		using_separator = Monom::using_separator,
		using_nums = Monom::using_nums,
		using_operators = "+-";

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