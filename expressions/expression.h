#pragma once
#include<iostream>

#include<exception>

#include<vector>
#include<string>
#include<map>
#include<stack>

#include"polynom.h"


template<typename T>
class Expression {
	enum class statesE {
		WAIT_LET_NUM_MIN_OPENBR,
		WAIT_NUM_DOT_OPER_CLOSEBR,
		WAIT_NUM,
		WAIT_NUM_OPER_CLOSEBR,
		WAIT_OPER_CLOSEBR,
		WAIT_LET_NUM_OPENBR,
		WAIT_LET_NUM_OPER_CLOSEBR,

		ERROR
	};

	
	std::string source_str, modified_str;
	std::string alph_nums = "0123456789",
		alph_letters = "abcdefghijklmnopqrstuvwABCDEFGHIJKLMNOPQRSTUVW",
		alph_operations = "-+/*",
		alph_opening_brackets = "({[",
		alph_closing_brackets = ")}]",
		alph_separator = ".";
	std::vector<std::string> postfix_form, variables_list;
	std::vector<std::string>alph_constants = {
	"pi","e"
	};
	T operands;

	std::map <std::string, Polynom> constants = {
		{"pi",Polynom("3.1415926535897932384626433832795")},
		{"e",Polynom("2.7182818284590452353602874713527")}
	};
	std::map < char, int > priority = {
		{'(',0},
		{'[',0},
		{'{',0},
		{'+',1},
		{'-',1},
		{'*',2},
		{'/',2},
	};

	Polynom res;
	bool is_correct;

	bool in(std::string str, std::vector<std::string> arr) {
		for (int i = 0; i < arr.size(); i++) {
			if (str == arr[i]) return true;
		}
		return false;
	}
	bool contains(char symb, std::string set) {
		for (int i = 0; i < set.size(); i++) {
			if (symb == set[i]) return true;
		}
		return false;
	}
	bool bracketsIsCorrect(Expression& exp) {
		std::stack<char> st;
		std::string str = exp.getSourceString();

		for (unsigned int i = 0; i < str.size(); i++) {
			if (contains(str[i], exp.getAcceptableOpeningBrackets()) && contains(str[i + 1], exp.getAcceptableClosingBrackets())) {
				return false;
			}
		}
		for (unsigned int i = 0; i < str.size(); i++) {
			if (str[i] == '(') st.push(')');
			if (str[i] == '{') st.push('}');
			if (str[i] == '[') st.push(']');

			if (!st.empty() && str[i] == st.top()) {
				st.pop();
			}
			else if (str[i] == ')' || str[i] == '}' || str[i] == ']')return false;

		}

		return st.empty();
	}

	bool expressionIsCorrect() {
		if (bracketsIsCorrect(*this) == 0) return false;
		statesE a = statesE::WAIT_LET_NUM_MIN_OPENBR;
		char symb = ' ';

		for (int i = 0; i < source_str.size(); i++) {
			symb = source_str[i];

			switch (a) {
			case(statesE::WAIT_LET_NUM_MIN_OPENBR):
				if (contains(symb, alph_nums)) {
					a = statesE::WAIT_NUM_DOT_OPER_CLOSEBR;
				}
				else if (contains(symb, alph_letters)) {
					a = statesE::WAIT_LET_NUM_OPER_CLOSEBR;
				}
				else if (symb == '-') {
					a = statesE::WAIT_LET_NUM_OPENBR;
				}
				else if (contains(symb, alph_opening_brackets)) {
					a = a;
				}
				else a = statesE::ERROR;

				break;
			case(statesE::WAIT_NUM_DOT_OPER_CLOSEBR):
				if (contains(symb, alph_nums)) {
					a = a;
				}
				else if (contains(symb, alph_separator)) {
					a = statesE::WAIT_NUM;
				}
				else if (contains(symb, alph_operations)) {
					a = statesE::WAIT_LET_NUM_OPENBR;
				}
				else if (contains(symb, alph_closing_brackets)) {
					a = statesE::WAIT_OPER_CLOSEBR;
				}
				else a = statesE::ERROR;

				break;
			case(statesE::WAIT_NUM):
				if (contains(symb, alph_nums)) {
					a = statesE::WAIT_NUM_OPER_CLOSEBR;
				}
				else a = statesE::ERROR;

				break;
			case(statesE::WAIT_NUM_OPER_CLOSEBR):
				if (contains(symb, alph_nums)) {
					a = a;
				}
				else if (contains(symb, alph_operations)) {
					a = statesE::WAIT_LET_NUM_OPENBR;
				}
				else if (contains(symb, alph_closing_brackets)) {
					a = statesE::WAIT_OPER_CLOSEBR;
				}
				else a = statesE::ERROR;

				break;
			case(statesE::WAIT_OPER_CLOSEBR):
				if (contains(symb, alph_operations)) {
					a = statesE::WAIT_LET_NUM_OPENBR;
				}
				else if (contains(symb, alph_closing_brackets)) {
					a = a;
				}
				else a = statesE::ERROR;

				break;
			case(statesE::WAIT_LET_NUM_OPENBR):
				if (contains(symb, alph_letters)) {
					a = statesE::WAIT_LET_NUM_OPER_CLOSEBR;
				}
				else if (contains(symb, alph_nums)) {
					a = statesE::WAIT_NUM_DOT_OPER_CLOSEBR;
				}
				else if (contains(symb, alph_opening_brackets)) {
					a = statesE::WAIT_LET_NUM_MIN_OPENBR;
				}
				else {
					a = statesE::ERROR;
				}

				break;
			case(statesE::WAIT_LET_NUM_OPER_CLOSEBR): {
				if (contains(symb, alph_letters) || contains(symb, alph_nums)) {
					a = a;
				}
				else if (contains(symb, alph_operations)) {
					a = statesE::WAIT_LET_NUM_OPENBR;
				}
				else if (contains(symb, alph_closing_brackets)) {
					a = statesE::WAIT_OPER_CLOSEBR; //------------------------------
				}
				else {
					a = statesE::ERROR;
				}
				break;
			}
			case(statesE::ERROR):
				return false;
				break;
			}
		}
		if (contains(symb, alph_nums) || contains(symb, alph_letters) || contains(symb, alph_closing_brackets)) {
			return true;
		}
		return false;
	}
	void cut() {

		std::stack<char> operations_stack;
		rewriteForUnaryMinus();
		if (is_correct == false) return;
		char cur_symb;
		std::string token;

		for (int i = 0; i < modified_str.size(); i++) {
			cur_symb = modified_str[i];
			if (contains(cur_symb, alph_operations) || contains(cur_symb, alph_opening_brackets) || contains(cur_symb, alph_closing_brackets)) {
				if (token != "") {

					postfix_form.push_back(token);
					if (in(token, alph_constants)) {
						operands.insert({ token,constants[token] });
					}
					else {
						variables_list.push_back(token);
						operands.insert({ token, (contains(token[0],alph_letters)) ? Polynom("0") : Polynom(token) });
					}
					token = "";
				}
			}
			if (contains(cur_symb, alph_opening_brackets)) {
				operations_stack.push(cur_symb);
			}
			else if (contains(cur_symb, alph_closing_brackets)) {
				while (!contains(operations_stack.top(), alph_opening_brackets)) {
					postfix_form.push_back(std::string(1, operations_stack.top()));
					operations_stack.pop();
				}
				operations_stack.pop();
			}
			else if (contains(cur_symb, alph_operations)) {
				while (operations_stack.empty() == false && (priority[cur_symb] <= priority[operations_stack.top()])) {
					postfix_form.push_back(std::string(1, operations_stack.top()));
					operations_stack.pop();

				}
				operations_stack.push(cur_symb);
			}

			if (contains(cur_symb, alph_nums) || contains(cur_symb, alph_letters) || contains(cur_symb, alph_separator))
				token += cur_symb;

		}
		if (token != "") {
			postfix_form.push_back(token);
			if (in(token, alph_constants))
				operands.insert({ token,constants[token] });
			else {
				operands.insert({ token, (contains(token[0],alph_letters)) ? Polynom("0") : 
					Polynom(token) });
				variables_list.push_back(token);
			}
		}
		while (operations_stack.empty() == false) {
			postfix_form.push_back(std::string(1, operations_stack.top()));
			operations_stack.pop();
		}
	}
	void calculate() {
		std::stack<Polynom> st;
		std::string lexem;
		Polynom v1, v2;
		for (int i = 0; i < postfix_form.size(); i++) {
			lexem = postfix_form[i];
			//------------------------------------------------HERE APPEND OPERATIONS
			if (lexem == "+") {
				v2 = st.top(); st.pop();
				v1 = st.top(); st.pop();

				st.push(v1 + v2);
			}
			else if (lexem == "-") {
				v2 = st.top(); st.pop();
				v1 = st.top(); st.pop();

				st.push(v1 - v2);
			}
			else if (lexem == "*") {
				v2 = st.top(); st.pop();
				v1 = st.top(); st.pop();
				st.push(v1 * v2);
			}
			else if (lexem == "/") {
				v2 = st.top(); st.pop();
				v1 = st.top(); st.pop();

				if (v2 == Polynom("0")) {
					throw std::exception("Division by zero");

					res = Polynom(); (1e+300 * 1e+300);//INFINITY
					return;
				}
				std::pair<Polynom, Polynom> del = v1 / v2;
				if (del.second == Polynom("0"))
					st.push((v1 / v2).first);
				else {
					throw std::exception("Polynoms couldn't be divided");
				}
			}
			else {
				st.push(operands[lexem]);
			}
		}
		if (st.empty() == false)
			res = st.top();
	}

	void clear() {
		Expression tmp;
		*this = tmp;
	}
	bool isVariable(std::string str) {
		if (contains(str[0], alph_nums)) return false;
		for (int i = 1; i < str.size(); i++)
			if (!(contains(str[i], alph_letters) || contains(str[i], alph_nums))) return false;
		return true;
	}
	void rewriteForUnaryMinus()
	{
		char cur_symb = ' ';
		std::string tmp;
		if (source_str[0] == '-')
			tmp += '0';
		tmp += source_str[0];

		for (int i = 1; i < source_str.size(); i++) {
			cur_symb = source_str[i];
			if (contains(source_str[i - 1], alph_opening_brackets) && cur_symb == '-')
				tmp += '0';
			tmp += cur_symb;
		}
		modified_str = tmp;
	}
	void delete_spaces(std::string& str) {
		std::string tmp;
		for (int i = 0; i < str.size(); i++)
			if (str[i] != ' ')
				tmp += str[i];
		str = tmp;
	}

	Expression& Expression::operator=(std::string str) {
		delete_spaces(str);

		std::string token1, token2;
		bool flag = true;

		for (int i = 0; i < str.size(); i++) {
			if (str[i] == '=') {
				if (flag == false)throw std::exception("Expression is not correct");
				flag = false;
				continue;
			}
			if (flag)
				token1 += str[i];
			else token2 += str[i];
		}
		if (!flag && token2.size() == 0)throw std::exception("Expression is not correct");

		if (token2.size() != 0) {
			if (in(token1, alph_constants))throw std::exception("Can't change value of constant");

			if (in(token2, alph_constants)) {
				operands[token1] = constants[token2];
			}
			else if (in(token2, variables_list)) {
				operands[token1] = operands[token2];
			}
			else {
				if (isVariable(token1) == false) throw std::exception("Variable is not correct");
				variables_list.push_back(token1);
				operands[token1] = Polynom(token2);
			}
			calculate();
		}
		else {
			Expression tmp2;
			tmp2.source_str = token1;
			tmp2.is_correct = tmp2.expressionIsCorrect();
			if (tmp2.is_correct)
				tmp2.cut();
			else if (tmp2.source_str.size() != 0) throw std::exception("Expression is not correct");
			if (tmp2.source_str != "")
				*this = tmp2;
			calculate();
		}


		return *this;
	}
public:
	Expression() :is_correct(false), res(Polynom("0")) { };
	Expression(std::string str) {
		source_str = str;

		is_correct = this->expressionIsCorrect();
		if (is_correct) {
			this->cut();

			this->calculate();
		}
	}

	std::string getSourceString() {
		return source_str;
	}

	Expression& operator=(Expression& exp) {
		if (this == &exp) return *this;
		source_str = exp.source_str;

		for (int i = variables_list.size(); i < exp.variables_list.size(); i++)
			variables_list.push_back(exp.variables_list[i]);// need to append but not to make copy
		for (auto it : exp.operands) {
			operands.emplace(it.first,it.second);
		}

		postfix_form = exp.postfix_form;
		is_correct = exp.is_correct;
		res = exp.res;
		return *this;
	}

	Polynom getResult() { return res; };
	bool isCorrect() { return is_correct; }
	std::string getAcceptableNums() { return alph_nums; }
	std::string getAcceptableOperations() { return alph_operations; }
	std::string getAcceptableOpeningBrackets() { return alph_opening_brackets; }
	std::string getAcceptableClosingBrackets() { return alph_closing_brackets; }
	std::string getAcceptableSeparators() { return alph_separator; }
	std::vector<std::string> getPostfixForm() { return postfix_form; }

	Expression& addExp(std::string str) {
		*this = str;
		return *this;
	};

	friend std::istream& operator>>(std::istream& istream, Expression& exp) {
		std::string tmp;
		std::getline(istream, tmp, '\n');
		exp = tmp;

		return istream;
	}
	friend std::ostream& operator<<(std::ostream& ostream, const Expression& exp) {
		if (exp.is_correct)
			ostream << "res) " << exp.source_str << "=" << exp.res;
		else if (exp.source_str != "")ostream << "Expression is not correct";
		return ostream;
	}
};
