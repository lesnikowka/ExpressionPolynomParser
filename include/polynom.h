#pragma once
#include"list.h"
#include"monom.h"

/*
Класс полином
примеры полиномов: 2x0x5^2+3x2^7
должен уметь:
	складывать/вычитать полиномы
	умножать на скаляр/моном/полином
	выводить полином
	вычислять в точке
*/

class Polynom {
	List<Monom> monoms;

	std::string using_alphabet = "xyz",
		using_symb_for_degree = "^",
		using_symb_for_multiplie = "*",
		using_separator = ".",
		using_nums = "0123456789",
		using_operators = "+-*";

	bool isCorrect();
	void sort();
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
	


	Polynom& operator=(const Polynom & m);
	bool operator==(const Polynom& m);



	friend std::istream& operator>>(std::istream& istream, Polynom& p);
	friend std::ostream& operator<<(std::ostream& ostream, Polynom& p);
};