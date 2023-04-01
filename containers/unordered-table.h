#pragma once

#include<vector>
#include<initializer_list>
#include<ostream>
template<typename T, typename D>
class UnorderedTable {
	std::vector<std::pair<T, D>> table;

public:
	UnorderedTable() = default;
	UnorderedTable(const UnorderedTable& t) = default;
	
	class iterator {
		std::pair<T, D>* it;
	public:
		friend UnorderedTable;
		iterator() :it(nullptr) {};
		iterator(std::pair<T,D>* p) {
			it = p;
		}
		iterator& operator=(const iterator& _it) {
			it = _it.it;
			return *this;
		}
		iterator operator++() {//++i
			it++;
			return *this;
		}
		iterator operator++(int) {//i++
			iterator tmp(*this);
			it++;
			return tmp;
		}
		iterator& operator--() {
			it--;
			return *this;
		}
		iterator& operator--(int) {
			iterator tmp(*this);
			it--;
			return tmp;
		}
		bool operator==(const iterator& _it) const {
			return it == _it.it;
		}
		bool operator!=(const iterator& _it) const {
			return !(*this==_it);
		}

		std::pair<T, D>& operator*() {
			return *it;
		}

	};

	iterator begin() {
		if (table.size() == 0)return iterator();
		return iterator(&table[0]); 
	}
	iterator end(){
		if (table.size() == 0)return iterator();
		iterator it(&table[table.size()-1]);
		it++;
		return it; 
	}
	
	iterator find(const T& key) {
		for (iterator i = begin(); i != end(); i++) {
			if (key == (*i).first) return i;
		}
		return end();
	}
	void insert(std::pair<T, D> p) {
		return emplace(p.first, p.second);
	}
	void emplace(T k,D e) {
		if (find(k) == end()) {
			table.push_back(std::make_pair(k, e));
		}
	};
	
	D& operator[](const T& key) {
		iterator it = find(key);
		if (it == end())emplace(key, D());
		return (*find(key)).second;
	}
	D& operator[](T&& key) {
		iterator it = find(key);
		if (it == end())emplace(key, D());
		return (*find(key)).second;
	}

	size_t size() {
		return table.size();
	}

	void erase(const T& key) {
		if (find(key) == end())
			throw std::exception("Index out of range");
		std::swap(*find(key) ,table[table.size()-1]);
		table.pop_back();
	};

	friend std::ostream& operator<<(std::ostream& ostream, const UnorderedTable& t) {
		for (int i = 0; i < t.table.size();i++){
			ostream << t.table[i].first <<" : " << t.table[i].second << '\n';
		}
		return ostream;
	}

};