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
		}
		iterator& operator++() {//++i
			it++;
			return *this;
		}
		iterator& operator++(int) {//i++
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
		bool operator==(const iterator& _it) {
			return it == _it.it;
		}
		bool operator!=(const iterator& _it) {
			return !(*this==_it);
		}

		std::pair<T, D>& operator*() {
			return *it;
		}

	};

	iterator begin() { return iterator(&table[0]); }
	iterator end(){
	iterator it(&table[table.size()-1]);
		it++;
		return it; }
	
	iterator find(const T& key) {
		for (iterator i = begin(); i != end(); i++) {
			if (key == (*i).first) return i;
		}
		return end();
	}
	void emplace(T k,D e) {
		table.push_back(std::make_pair(k,e));
	};
	
	void erase(const T& key) {
		if (find(key) == end())
			throw "Index out of range";
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