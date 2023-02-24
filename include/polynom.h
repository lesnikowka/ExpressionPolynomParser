#pragma once

#include <vector>
#include <list>
#include <algorithm>

#include "monom.h"

class Polynom {


	std::list<Monom> monoms;
	

	void sort() {
		//monoms.sort();
		//
		//if (monoms.size() >= 2) {
		//	auto current = monoms.begin();
		//	auto next = monoms.begin();
		//	++next;
		//
		//	while (next != monoms.end()) {
		//		if ((*current).isSimilar(*next)) {
		//			*next += *current;
		//			if ((*next).getCoef() == 0) {
		//				next = monoms.erase(next);
		//			}
		//			monoms.erase(current);
		//			current = next;
		//		}
		//
		//		else
		//			++current;
		//
		//		++next;
		//	}
		//}
	}
	void cut() {}
public:
	const std::string using_alphabet = "xyz";
	const std::string using_symb_for_degree = "^";
	const std::string using_symb_for_multiplie = "*";
	const std::string using_separator = ".";
	const std::string using_nums = "0123456789";
	const std::string using_operators = "+-*^";

	Polynom() = default;
	Polynom(const Polynom& p) = default;
	Polynom(std::string str) = delete;

	double calculate(std::vector<double> vect) const { return double(); }

	Polynom& operator+=(const Polynom& p) { 
		//auto this_it = monoms.begin();
		//auto p_it = p.monoms.begin();
		//bool insert_done;
		//
		//while (p_it != p.monoms.end()) {
		//	insert_done = false;
		//	while (this_it != monoms.end()) {
		//		if ((*this_it).isSimilar(*p_it)) {
		//			*this_it += *p_it;
		//			if ((*this_it).getCoef() == 0) {
		//				this_it = monoms.erase(this_it);
		//			}
		//			else {
		//				++this_it;
		//			}
		//			insert_done = true;
		//		}
		//		else if ((*this_it) > (*p_it)) {
		//			monoms.insert(this_it, *p_it);
		//			insert_done = true;
		//			++this_it;
		//		}
		//		else {
		//			++this_it;
		//		}
		//	}
		//	if (!insert_done) {
		//		monoms.push_back(*p_it);
		//	}
		//	++p_it;
		//}
		return *this; 
	}
	Polynom operator+(const Polynom& p) const {
		Polynom result(*this);
		result += p;
		return result;
	}
	
	Polynom& operator-=(const Polynom& p) { 
		operator+=(p * (-1));
		return *this;
	}
	Polynom operator-(const Polynom& p) const { 
		Polynom result(*this);
		result -= p;
		return result;
	}
	
	Polynom& operator*=(const Polynom& p) { return*this; }
	Polynom operator*(const Polynom& p) const { return *this; }


	Polynom& operator*=(double c) { 
		for (Monom& i : monoms)
			i *= c;
		return *this;
	}
	Polynom operator*(double c) const{ 
		Polynom result;
		result *= c;
		return result;
	}
	
	std::pair<Polynom, Polynom> operator/(const Polynom& p) const { return { *this, *this }; }
	
	Polynom integral(char s) { 
		Polynom result(*this);
		for (Monom& i : result.monoms)
			i = i.integral(s);
		return result;
	}
	Polynom derivative(char s) { 
		Polynom result(*this);
		for (Monom& i : result.monoms)
			i = i.derivative(s);
		return result;
	}
	Polynom& operator=(const Polynom& m) = default;
	bool operator==(const Polynom& p) const noexcept {
		if (monoms != p.monoms)
			return false;
		return true;
	}
	bool operator!=(const Polynom& p) const noexcept {
		return !operator==(p);
	}

	friend std::istream& operator>>(std::istream& istream, Polynom& p) { return istream; }
	friend std::ostream& operator<<(std::ostream& ostream, Polynom& p) { return ostream; }
};