#include<vector>
#include<initializer_list>
#include<ostream>
template<typename T, typename D>
class UnorderedTable {
	std::vector<std::pair<T, D>> table;

public:
	UnorderedTable() = default;
	UnorderedTable(const UnorderedTable& t) = default;

	int find(const T& key) {
		for (int i = 0; i < table.size(); i++) {
			if (key == table[i].first) return i;
		}
		return table.size();
	};
	void emplace(std::pair<T, D> p) {
		table.push_back(p);
	};
	void emplace(T k,D e) {
		table.push_back(std::make_pair(k,e));
	};


	void erase(const T& key) {
		if (find(key) == table.size()) throw "Index out of range";
		std::swap(table[find(key)],table[table.size()-1]);
		table.pop_back();
	};

	friend std::ostream& operator<<(std::ostream& ostream, const UnorderedTable& t) {
		for (int i = 0; i < t.table.size();i++){
			ostream << t.table[i].first <<" : " << t.table[i].second << '\n';
		}
		return ostream;
	}

};