#pragma once

#include <vector>
#include <list>
#include <algorithm>

#include "monom.h"

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
				if (m1.degree[i] < m2.degree[i])
					return true;

				else if (m1.degree[i] > m2.degree[i])
					return false;
			}

			return false;
		}
	};

	void sort() {
		Comparator comp;
		monoms.sort(comp);
		
		if (monoms.size() >= 2) {
			auto current = monoms.begin();
			auto next = monoms.begin();
			++next;
		
			while (next != monoms.end()) {
				if ((*current).isSimilar(*next)) {
					*next += *current;
					if ((*next).getCoef() == 0) {
						next = monoms.erase(next);
					}
					monoms.erase(current);
					current = next;
				}
		
				else
					++current;
		
				++next;
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
					monoms.push_back(m);
				}
				start = i;
			}
			else if (str[i] == using_operators[0]) {
				m = Monom();
				m.cut(str.substr(start, i - start));
				monoms.push_back(m);
				start = i + 1;
			}
			else if (i == str.size()) {
				m = Monom();
				m.cut(str.substr(start, i - start));
				monoms.push_back(m);
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
				}
				else if (comp(*p_it,*this_it)) {
					monoms.insert(this_it, *p_it);
					insert_done = true;
					++this_it;
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
	Polynom& operator+=(const Monom& m) {
		Polynom p(m);
		operator+=(p);
		return *this;
	}
	Polynom operator+(const Monom& m) const {
		Polynom p(m), result;
		result += m;
		return *this;
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
	Polynom& operator-=(const Monom& m) {
		Polynom p(m);
		operator-=(p);
		return *this;
	}
	Polynom operator-(const Monom& m) const {
		Polynom p(m), result;
		result -= m;
		return *this;
	}


	Polynom& operator*=(const Monom& m) { 
		for (Monom& e : monoms)
			e *= m;
		return *this;
	}
	Polynom operator*(const Monom& m) const {
		Polynom result(*this);
		result *= m;
		return result;
	}
	Polynom operator*(const Polynom& p) const {
		Polynom current;
		Polynom result;
		for (const Monom& e : p.monoms) {
			current = *this;
			current *= e;
			std::cout << "current: " << current << std::endl;
			result += current;
			std::cout <<"result: " << result << std::endl;
		}
		return result;
	}
	Polynom& operator*=(const Polynom& p) {
		operator=((*this) * p);
		return *this;
	}
	


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
	
	Polynom integral(char s) const{ 
		Polynom result(*this);
		for (Monom& i : result.monoms)
			i = i.integral(s);
		return result;
	}
	Polynom derivative(char s) const { 
		Polynom result(*this);
		for (Monom& i : result.monoms)
			i = i.derivative(s);
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

	friend std::istream& operator>>(std::istream& istream, Polynom& p) { 
		std::string str;
		istream >> str;
		p.cut(str);
		return istream;
	}
	friend std::ostream& operator<<(std::ostream& ostream, Polynom& p) { 
		bool begin = true;
		for (auto& e : p.monoms) {
			if (e.getCoef() > 0 && !begin) 
				ostream << "+";
			begin = false;

			ostream << e;
		}

		return ostream;
	}
};