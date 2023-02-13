#pragma once
#include"list.h"
#include<vector>
#include<string>

template<typename T>
int findIndex(T elem,std::vector<T> vect) {
	int index=0;
	for (index; index < vect.size(); index++) {
		if (elem == vect[index]) return index;
	}
	return -1;

}
bool in(char symb,std::string alph) {
	for (int i = 0; i < alph.size(); i++) {
		if (symb == alph[i]) return true;
	}
	return false;
}
enum class states {
	letter,
	number,
	number_letter_degree_multip,
	number_but_for_degree,
	number_letter_mulptip,
	ERROR
};

class Monom {
	std::vector<int> degree;
	double coef;


	std::string using_alphabet = "xyz";
	std::string using_symb_for_degree = "^";
	std::string using_symb_for_multiplie = "*";
	std::string using_separator = ".";
	std::string using_nums = "0123456789";
	std::string using_operators = "+-*^";


	void sortIndexes();
	void cut(std::string str);
	bool isCorrect();

public:
	Monom()=default;
	Monom(const Monom& m) = default;
	Monom(std::string str);


	double calculate(std::vector<double> vect);
	bool isSimilar(const Monom& m);

	Monom& operator=(const Monom& m);
	Monom& operator*=(const Monom& m);
	Monom operator*(const Monom& m);
	bool operator==(const Monom& m);
	bool operator!=(const Monom& m);
	bool operator<=(const Monom& m);
	bool operator>=(const Monom& m);
	bool operator<(const Monom& m);
	bool operator>(const Monom& m);
	

	friend std::istream& operator>>(std::istream& istream, Monom& m);
	friend std::ostream& operator<<(std::ostream& ostream, Monom& m);


};
