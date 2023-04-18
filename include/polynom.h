#pragma once

#include <vector>
#include <list>
#include <algorithm>
#include "monom.h"
#include <iostream>

class Polynom {
	std::list<Monom> monoms;
	

	const std::string using_alphabet = "xyz";
	const std::string using_symb_for_degree = "^";
	const std::string using_symb_for_multiplie = "*";
	const std::string using_separator = ".";
	const std::string using_nums = "0123456789";
	const std::string using_operators = "+-";

	class Comparator {
	public:
		bool operator()(const Monom& m1, const Monom& m2)  const noexcept {
			for (size_t i = 0; i < m1.degree.size(); i++) {
				if (m1.degree[i] > m2.degree[i])
					return true;
	
				else if (m1.degree[i] < m2.degree[i])
					return false;
			}
	
			return false;
		}
	};
	bool isDivider(const Monom& m1, const Monom& m2) {
		std::vector<int> degree1 = m1.getDegrees(), degree2 = m2.getDegrees();

		for (size_t i = 0; i < degree1.size(); i++) {
			if (degree1[i] < degree2[i]) {
				return false;
			}
		}
		return true;
	}
	Monom getDivider(const Monom& m1, const Monom& m2) {
		Monom result;
		result.coef = m1.coef / m2.coef;
		std::vector<int> degree1 = m1.getDegrees(), degree2 = m2.getDegrees();

		for (size_t i = 0; i < degree1.size(); i++) {
			result.degree[i] = degree1[i] - degree2[i];
		}
		return result;
	}

	void sort() {
		Comparator comp;
		monoms.sort(comp);

		
		if (monoms.size() >= 2) {
			auto current = monoms.begin();
			for (auto next = (monoms.begin()); ++next != monoms.end();){
				if ((*current).isSimilar(*next)) {
					*next += *current;
					if ((*next).getCoef() == 0) {
						next = monoms.erase(next);
					}
					monoms.erase(current);
					current = next;
				}
				else if (current != monoms.end())
					++current;
			}
		}
	}
	void cut(const std::string& str) {
		Monom m;

		size_t start = 0;
		for (size_t i = 0; i <= str.size(); i++) {
			if (str[i] == using_operators[1]) {
				if (i != 0) {
					m = Monom();
					m.cut(str.substr(start, i - start));
					if (m.getCoef() != 0) {
						monoms.push_back(m);
					}
				}
				start = i;
			}
			else if (str[i] == using_operators[0]) {
				m = Monom(str.substr(start, i - start));
				if (m.getCoef() != 0) {
					monoms.push_back(m);
				}
				start = i + 1;
			}
			else if (i == str.size()) {
				m = Monom(str.substr(start, i - start));
				if (m.getCoef() != 0) {
					monoms.push_back(m);
				}
			}
		}

		sort();
	}
public:

	Polynom() = default;
	Polynom(const Polynom& p) = default;
	Polynom(const std::string& str) {
		cut(str);
	}
	Polynom(const Monom& m) {
		monoms.push_back(m);
	}

	Polynom& operator=(const Polynom& m) { 
		monoms = m.monoms; 
		return *this;
	}

	double calculate(std::vector<double> vect) const { 
		double result = 0;
		for (const Monom& i : monoms) {
			result += i.calculate(vect);
		}
		return result;
	}

	Polynom& operator+=(const Polynom& p) { 
		auto this_it = monoms.begin();
		auto p_it = p.monoms.begin();
		bool insert_done;
		Comparator comp;
		
		while (p_it != p.monoms.end()) {
			insert_done = false;
			while (this_it != monoms.end()) {
				if ((*this_it).isSimilar(*p_it)) {
					*this_it += *p_it;
					if ((*this_it).getCoef() == 0) {
						this_it = monoms.erase(this_it);
					}
					else {
						++this_it;
					}
					insert_done = true;
					break;
				}
				else if (comp(*p_it,*this_it)) {
					monoms.insert(this_it, *p_it);
					insert_done = true;
					break;
				}
				else {
					++this_it;
				}
			}
			if (!insert_done) {
				monoms.push_back(*p_it);
			}
			++p_it;
		}

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
	Polynom operator*(const Polynom& p) const {
		Polynom current;
		Polynom result;
		for (const Monom& e : p.monoms) {
			current = *this;
			current *= e;
			result += current;
		}
		result.sort();
		return result;
	}
	Polynom& operator*=(const Polynom& p) {
		operator=((*this) * p);
		return *this;
	}
	
	Polynom& operator+=(const Monom& m) {
		if (m.getCoef() != 0) {
			Polynom p(m);
			operator+=(p);
		}
		return *this;
	}
	Polynom operator+(const Monom& m) const {
		Polynom result(*this);
		result += m;
		return result;
	}
	Polynom& operator-=(const Monom& m) {
		if (m.getCoef() != 0) {
			operator+=(m * (-1));
		}
		return *this;
	}
	Polynom operator-(const Monom& m) const {
		Polynom result(*this);
		if (m.getCoef() != 0) {
			result -= m;
		}
		return result;
	}
	Polynom& operator*=(const Monom& m) {
		if (m.getCoef() != 0) {
			for (Monom& e : monoms)
				e *= m;
		}
		else {
			monoms.clear();
		}

		return *this;
	}
	Polynom operator*(const Monom& m) const {
		Polynom result;
		if (m.getCoef() != 0) {
			result = *this;
			result *= m;
		}
		
		return result;
	}

	Polynom& operator*=(double c) { 
		if (c != 0) {
			for (Monom& i : monoms)
				i *= c;
		}
		else {
			monoms.clear();
		}
		return *this;
	}
	Polynom operator*(double c) const{ 
		Polynom result(*this);
		if (c != 0) {
			result *= c;
		}
		return result;
	}

	std::pair<Polynom, Polynom> operator/(Polynom p) { 

		Polynom remainder = *this, quotient;
		Monom div;

		Monom dl = *(p.monoms.begin());


		auto de = remainder.monoms.begin();
		while(de != remainder.monoms.end()){
			if (isDivider(*de, dl)) {
				div = getDivider(*de, dl);
				quotient += div;
				Polynom tmp = p * div;
				remainder -= tmp;
				de = remainder.monoms.begin();
			}
			else 
				++de;
		}
		
		return { quotient, remainder }; 
	}
	
	Polynom integral(char s) const{ 
		Polynom result(*this);
		for (Monom& i : result.monoms)
			i = i.integral(s);
		return result;
	}
	Polynom derivative(char s) const { 
		Polynom result(*this);

		std::list<Monom>::iterator it = result.monoms.begin();

		while (it != result.monoms.end()) {
			(*it) = (*it).derivative(s);
			
			if ((*it).getCoef() == 0)
				it = result.monoms.erase(it);
			
			else if (it != result.monoms.end())
				++it;
		}

		return result;
	}

	bool operator==(const Polynom& p) const noexcept {
		if (monoms != p.monoms)
			return false;
		return true;
	}
	bool operator!=(const Polynom& p) const noexcept {
		return !operator==(p);
	}

	std::string str() const {
		bool begin = true;
		std::string result;

		for (auto& e : monoms) {
			if (e.getCoef() > 0 && !begin)
				result += "+";
			begin = false;

			result += e.str();
		}

		if (result.size() == 0) result += "0";

		return result;
	}

	friend std::istream& operator>>(std::istream& istream, Polynom& p) {
		p.monoms.clear();
		std::string str;
		istream >> str;
		p.cut(str);

		return istream;
	}
	friend std::ostream& operator<<(std::ostream& ostream, Polynom p) { 
		ostream << p.str();

		return ostream;
	}
};