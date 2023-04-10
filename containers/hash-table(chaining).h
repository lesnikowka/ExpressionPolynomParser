#pragma once
#include<vector>
#include<list>
#include<string>
#include<ctime>
#include<cmath>


template<typename T, typename D>
class HashTableC {
	friend class iterator;
	struct pair {
		T first;
		D second;
		pair() = default;
		pair(T first,D second):first(first),second(second){}
		pair(const pair& p):first(p.first),second(p.second){}
		friend std::ostream& operator<<(std::ostream& ostream, const pair& p) {
			ostream<< p.first << ":" << p.second;
			return ostream;
		}
	};

	//size of table
	size_t capacity;
	
	std::vector<std::list<pair>> table;

	//settings for hash()
	int a, b,c;
	std::vector<int> simp_nums = { 13,53,151, 503,1553, 5101, 2764437 };//, 1000000007};
	int p = 1000000007,pstr=17;
	
	//counter of seconds
	int size;

	float per_of_fill;
	
public:
	
	HashTableC() {
		size = 0;
		capacity = simp_nums[0];
		per_of_fill = 0.f;

		srand(time(0));

		a = rand() % (1007 * capacity);
		b = rand() % 13;
		c = capacity;
		table.resize(capacity);
	};
	HashTableC(size_t cap) {
		size = 0;
		c = cap;
		capacity = cap;
		per_of_fill = 0.f;

		srand(time(0));

		getNewCoef(capacity);
		table.resize(capacity);
	}

	class iterator {
		friend class HashTableC;
		typename std::list<pair>::iterator it;
		size_t index;
		std::vector<std::list<pair>>* table;
		size_t capacity;
		iterator() = delete;
		iterator(typename std::list<pair>::iterator iter, size_t index, std::vector<std::list<pair>>* table) {
			this->index = index;
			this->it = iter;

			this->table = table;
			this->capacity = table->size();
		}
		

	public:
		iterator(const iterator& iter) {
			this->index = iter.index;
			this->it = iter.it;
			
			this->table = iter.table;
			this->capacity = iter.capacity;
		}
		iterator& operator=(const iterator& iter) {
			this->index = iter.index;
			this->it = iter.it;

			this->table = iter.table;
			this->m = iter.m;
			return *this;
		}
		bool operator==(const iterator& iter) const {
			return (index == iter.index &&it == (iter.it));
		}
		bool operator!=(const iterator& iter) const{
			return !operator==(iter);
		}

		pair& operator*() {
			if (it == (*table)[index].end())throw("Iterator points to the end");
			return *it;
		}
		
		iterator operator++(int) {
			iterator tmp(*this);
			operator++();
			return tmp;
		}
		iterator& operator++() {

			typename std::list<pair>::iterator tmp = it;
			if (it != (*table)[index].end())
				tmp++;

			if (tmp == (*table)[index].end()) {
				if (index != capacity - 1) {
					do {
						index++;
					} while ((*table)[index].begin() == (*table)[index].end() && (index != capacity - 1));
					it = (*table)[index].begin();
				}
				else {
					it++;
				}
				
			}
			else {
				it++;
			}
			return *this;
		}
	};
	
	int takeNextSimp() {
		for (auto it : simp_nums) {
			if (it > capacity)
				return it;
		}
		return simp_nums[simp_nums.size() - 1];
	}
	void repack() {
		size_t index;
		size_t new_capacity = takeNextSimp();
		per_of_fill /= 2;

		getNewCoef(new_capacity);
		std::vector<std::list<pair>> new_table; new_table.resize(new_capacity);
		for (iterator it = begin(); it != end(); it++) {
			if (it != end(it.index)) {
				index = hash((*it).first);
				new_table[index].push_front(*it);
			}
		}
		table = new_table;
		capacity = new_capacity;
	}

	iterator begin(size_t index = 0) {
		while (index<(capacity-1)&&table[index].size()==0) {
			index++;
		}
		return iterator(table[index].begin(),index,&table);
	}
	iterator end(size_t index=-1) {
		if (index == -1)index = capacity - 1;
		return iterator(table[index].end(),index,&table);
	}
	template<typename T>
	int hash(const T& first) {
		return first.hash();
	}
	int hash(std::string& first)
	{
		int res = 0;
		for (int i = 0; i < first.size();i++) {
			res += (int)first[i]*pow(pstr,i);
		}
		return res%capacity;
	}
	int hash(int& first) {
		int h = ((a * first + b) % p) % c;
		if (h < 0)h +=c;
		return h;
	}
	void getNewCoef(size_t capacity) {

		a = rand() + 1000;
		b = rand() % 13;
		c = capacity;
	}

	iterator find(T first) {
		size_t index = hash(first);
		iterator it = begin(index);
		int start_index = it.index;

		while (it.index==start_index&&it != end(it.index) && (*it).first != first) {
			it++;
		}
		if (it.index != start_index)return end();
		return it;
	}
	D& operator[](const T& first) {
		iterator it = find(first);
		if (it == end(it.index))
			emplace(first, D());
		return (*find(first)).second;
	}
	D& operator[](T&& first) {
		iterator it = find(first);
		if (it == end(it.index))emplace(first, D());
		return (*find(first)).second;
	}

	void insert(std::pair<T, D> p) {
		return emplace(p.first, p.second);
	}
	void emplace(T first,D second) {
		int index = hash(first);
		iterator it = find(first);
		if (it != end()) return;
		table[index].push_front(pair(first,second));
		size++;
		per_of_fill = (float)size / (float)capacity;
		if (per_of_fill >= 0.7f) 
			repack();
	}

	void erase(T first) {
		iterator second = find(first);
		size_t index = hash(first);
		if (second == end()) throw "second not founded";
		table[index].erase(second.it);
		size--;
		per_of_fill = size / capacity;
	}
	
	int getA() { return a; }
	int getB() { return b; }
	size_t getSize() { return size; }
	size_t getCapacity() { return capacity; }
	
	friend std::ostream& operator<<(std::ostream& ostream,const HashTableC& n) {
		bool flag = true;
		for (auto col : n.table) {
			flag = false;
			for (auto row : col) {
				ostream<< row.first << ":" << row.second<<' ';
				flag = true;
			}
			if(flag)
			ostream << '\n';
		}
		return ostream;
	}
};