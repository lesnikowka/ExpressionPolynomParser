#pragma once
#include<vector>
#include<string>
#include<iostream>


enum states {
	letter,
	number,
	letter_number_mult,
	letter_degree_mult,
	number_letter,
	number_dot_letter,
	number_letter_after_coef,
	number_in_coef,
	number_letter_minus,

	ERROR
};


class Monom {
	friend class Polynom;
	std::vector<int> degree;
	double coef;
	bool correctness;

	const std::string using_alphabet = "xyz";
	const std::string using_symb_for_degree = "^";
	const std::string using_symb_for_multiplie = "*";
	const std::string using_separator = ".";
	const std::string using_nums = "0123456789";
	const std::string using_operators = "+-*^";
	
	int findIndex(char elem, std::string str) {
		int index = 0;
		for (index; index < str.size(); index++) {
			if (elem == str[index]) return index;
		}
		return -1;

	}

	bool in(char symb, std::string alph) {
		for (int i = 0; i < alph.size(); i++) {
			if (symb == alph[i]) return true;
		}
		return false;
	}

	void cut(std::string str) {
		coef = 0;
		char cur_symb, next_symb;
		std::string lexem;
		int i = 0;

		//get coef -- start
		while (i < str.size() && in(str[i], using_alphabet) == false) {
			lexem += str[i];
			i++;
		}
		if (lexem.size() == 0) coef = 1;
		else if (lexem == "-") coef = -1;
		else coef = std::stod(lexem);
		lexem = "";
		//get coef -- end
		

		bool degree_symb_founded=false;
		std::string cur_degree;
		for (i; i < str.size(); i++) {
			cur_symb = str[i];
			next_symb = str[(str.size()==(i-1)?i:(i+1))];
			if (in(cur_symb, using_symb_for_degree)) {
				degree_symb_founded = true;
				continue;
			}

			if (degree_symb_founded)
				cur_degree += cur_symb;
			else 
				lexem += cur_symb;

			
			if (in(next_symb, using_alphabet)||i==str.size()-1) {
				if(degree_symb_founded)
				degree[findIndex(lexem[0],using_alphabet)] += std::stod(cur_degree);
				else
				{
					degree[findIndex(lexem[0], using_alphabet)]+=1;
				}
				lexem = "";
				cur_degree = "";
				degree_symb_founded = false;
			}
		}
	
	};
	bool isCorrect( const std::string& str) {
		char cur_symb='?';//using uncorrect for monom cur_symb
		enum states a=states::number_letter_minus;
		for (int i = 0; i < str.size(); i++) {
			cur_symb = str[i];
			switch (a) {
			case(states::number_letter_minus):
				if (in(cur_symb, using_nums)) {
					a = states::number_dot_letter;
				}
				else if (in(cur_symb, using_alphabet)) {
					a = states::letter_degree_mult;
				}
				else if (cur_symb=='-') {
					a = states::number_letter;
				}
				else {
					a = states::ERROR;
				}
				break;
			case(states::number_letter):
				if (in(cur_symb, using_nums)) {
					a = states::number_dot_letter;
				}
				else if (in(cur_symb, using_alphabet)) {
					a = states::letter_degree_mult;
				}
				else {
					a = states::ERROR;
				}
				break;
			case(states::number_dot_letter):
				if (in(cur_symb, using_nums)) {
					a = a;
				}
				else if (in(cur_symb, using_separator)) {
					a = states::number_in_coef;
				}
				else if (in(cur_symb, using_alphabet)) {
					a = states::letter_degree_mult;
				}
				else {
					a = states::ERROR;
				}
				break;
			case(states::number_in_coef) :
				if (in(cur_symb, using_nums)) {
					a = states::number_letter_after_coef;
				}
				else {
					a = states::ERROR;
				}
				break;
			case(states::number_letter_after_coef):
				if (in(cur_symb, using_nums)) {
					a = a;
				}
				else if (in(cur_symb, using_alphabet)) {
					a = states::letter_degree_mult;
				}
				else {
					a = states::ERROR;
				}
				break;
			case(states::letter_degree_mult):
				if (in(cur_symb, using_alphabet)) {
					a = a;
				}
				else if (in(cur_symb,using_symb_for_degree)) {
					a = states::number;
				}
				else if (in(cur_symb,using_symb_for_multiplie)) {
					a = states::letter;
				}
				else {
					a = states::ERROR;
				}
				break;
			case(states::number):
				if (in(cur_symb, using_nums)) {
					a = states::letter_number_mult;
				}
				else {
					a = states::ERROR;
				}

				break;
			case(states::letter_number_mult):
				if (in(cur_symb,using_nums)) {
					a=a;
				}
				else if (in(cur_symb, using_alphabet)) {
					a = states::letter_degree_mult;
				}
				else if (in(cur_symb,using_symb_for_multiplie)) {
					a = states::letter;
				}
				else { 
					a = states::ERROR;
				}
				break;
			case(states::letter):
				if (in(cur_symb, using_alphabet)) {
					a = states::letter_degree_mult;
				}
				else {
					a = states::ERROR;
				}
				break;
			case(states::ERROR):
				return false;
				break;

			}
		}
		if (a == states::ERROR || !(in(cur_symb,using_alphabet)||in(cur_symb,using_nums)))
			return false;
		return true;
	};

public:
	

	Monom() {
		degree.resize(using_alphabet.size(),0);
		coef = 0;
		correctness = true;
	};
	Monom(const Monom& m) = default;
	Monom(std::string str) {
		degree.resize(using_alphabet.size(), 0);
		coef = 0;
		correctness = isCorrect(str);
		if (correctness)
			cut(str);
		else if(str.size()!=0) throw "Monom is not correct";
	};


	double calculate(std::vector<double> vect) const {
		if (vect.size() != degree.size()) throw "Sizes are not equal";
		double result =coef;
		for (int i = 0; i < vect.size(); i++) {
			for (int j = 0; j < degree[i]; j++) {
				result *= vect[i];
			}
		}
		return result;
	};
	bool isSimilar(const Monom& m)const {
		for (int i = 0; i < degree.size(); i++) {
			if (degree[i] != m.degree[i])return false;
		}
		return true;
	};

	Monom& operator=(const Monom& m) {
		correctness = m.correctness;
		degree = m.degree;
		coef = m.coef;

		return *this;
	};
	Monom& operator*=(const Monom& m) {
		coef *= m.coef;
		for (int i = 0; i < degree.size(); i++) {
			degree[i] += m.degree[i];
		}
		return *this;
	};
	Monom operator*(const Monom& m) const {
		Monom tmp(*this);
		tmp *= m;
		return tmp;
	};

	Monom& operator*=(double m) {
		coef *= m;
		return *this;
	};
	Monom operator*(double m) const{
		Monom tmp(*this);
		tmp.coef *= m;
		return tmp;
		};
	Monom& operator+=(const Monom& m) {
		if (isSimilar(m)) { coef += m.coef; return *this; }
		else throw "Monoms are not similar";
	}
	Monom operator+(const Monom& m) const {
		Monom tmp(*this);
		tmp += m;
		return tmp;
	}
	Monom& operator-=(const Monom& m) {
		if (isSimilar(m)) { coef -= m.coef; return *this; }
		else throw "Monoms are not similar";
	}
	Monom operator-(const Monom& m) const {
		Monom tmp(*this);
		tmp -= m;
		return tmp;
	}

	Monom derivative(char var) {
		if (!in(var, using_alphabet)) throw "Uncorrect letter";
		int index = findIndex(var,using_alphabet);
		if (degree[index] == 0) return Monom();
		Monom m(*this);
		m.coef *= m.degree[index];
		m.degree[index]=(m.degree[index]<0)?0:(m.degree[index]-1);
		return m;
	}
	Monom integral(char var) {
		if (!in(var, using_alphabet)) throw "Uncorrect letter";
		Monom m(*this);
		if (coef == 0) return m;
		int index = findIndex(var, using_alphabet);
		
		m.degree[index] += 1;
		m.coef /= (m.degree[index]);
		return m;
	}

	bool operator==(const Monom& m)const noexcept {
		if (coef != m.coef) return false;
		return isSimilar(m);
	};
	 bool operator!=(const Monom& m)const  noexcept {
		return !operator==(m);
	};
	bool operator<=(const Monom& m) const noexcept {
		int degsum1=0, degsum2=0;
		for (int i = 0; i < degree.size(); i++) {
			degsum1 += degree[i];
			degsum2 += m.degree[i];
		}
		
		if (degsum1 < degsum2)return 1;
		else if (degsum1 > degsum2) return 0;

		for (int i = 0; i < degree.size(); i++) {
			if (degree[i] > m.degree[i]) return 0;
			else if (degree[i] < m.degree[i]) return 1;
		}
		return 1;

	};
	bool operator>=(const Monom& m) const noexcept {
		return !(operator<(m));
	};
	bool operator<(const Monom& m) const noexcept {
		return (!isSimilar(m) && operator<=(m));
	};
	  bool operator>(const Monom& m)const  noexcept {
		return (!isSimilar(m) && operator>=(m));
	};

	  std::string eraseExcessZeroes(const std::string& s) const{
		  int lenght = s.size();
		  for (int i = s.size() - 1; i && (s[i] == '0' || s[i] == '.'); i--) lenght--;
		  return s.substr(0, lenght);
	  }
	
	  std::string str() const{
		  int tmp = 0;
		  std::string result;
		  for (int i = 0; i < degree.size(); i++)
			  tmp += degree[i];
		  if (tmp == 0) {
			  result += eraseExcessZeroes(std::to_string(coef));
		  }
		  else {
			  if (coef == -1) result += "-";
			  else if (coef != 1) result+= eraseExcessZeroes(std::to_string(coef));
			  for (int i = 0; i < using_alphabet.size(); i++) {
				  if (degree[i] != 0) {
					  result += using_alphabet[i];
					  if (degree[i] != 1)
						  result += "^" + std::to_string(degree[i]);
				  }
			  }
		  }
		  return result;
	}

	friend std::istream& operator>>(std::istream& istream, Monom& m) {
		std::string str;
		istream >> str;
		m = Monom(str);
		return istream;
	};
	friend std::ostream& operator<<(std::ostream& ostream, const Monom& m) {
		ostream << m.str();
		return ostream;
	};

	double getCoef() const noexcept{ return coef; }
	std::vector<int> getDegrees() const noexcept { return degree; };
	bool getCorrectness() const noexcept { return correctness; }
};