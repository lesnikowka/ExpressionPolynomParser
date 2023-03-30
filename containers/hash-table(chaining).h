#pragma once
#include<vector>
#include<list>
#include<string>


template<typename T, typename D>
class HashTableC {
	friend class iterator;
	struct pair {
		T key;
		D elem;
		pair() = default;
		pair(T key,D elem):key(key),elem(elem){}
		pair(const pair& p):key(p.key),elem(p.elem){}
		friend std::ostream& operator<<(std::ostream& ostream, const pair& p) {
			ostream<< p.key << ":" << p.elem;
			return ostream;
		}
	};

	//size of table
	size_t capacity;
	
	std::vector<std::list<pair>> table;

	//settings for hash()
	int a, b,c;
	std::vector<int> simp_nums = {13,53,151, 503,1553,5101,2764437,1000000007};
	int p = 1000000007;
	
	//counter of elements
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
		bool operator==(const iterator& iter) {
			return (index == iter.index &&it == (iter.it));
		}
		bool operator!=(const iterator& iter) {
			return !operator==(iter);
		}

		pair& operator*() {
			//if (it == (*table)[index].end())throw("Iterator points to the end");
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
				index = hash((*it).key);
				new_table[index].push_front(*it);
			}
		}
		table = new_table;
		capacity = new_capacity;
	}

	iterator begin(size_t index=0) {
		return iterator(table[index].begin(),index,&table);
	}
	iterator end(size_t index=-1) {
		if (index == -1)index = capacity - 1;
		return iterator(table[index].end(),index,&table);
	}

	int hash(std::string key)
	{
		int res = 0;
		for (int i = 0; i < key.size();i++) {
			res += (int)key[i]*pow(p,i);
		}
		return res%capacity;
	}
	int hash(int key) {
		return ((a*key+b)%p) % c;
	}
	void getNewCoef(size_t capacity) {

		a = rand() + 1000;
		b = rand() % 13;
		c = capacity;
	}

	iterator find(T key) {
		size_t index = hash(key);
		iterator it = begin(index);

		while (it != end(it.index) && (*it).key != key) {
			it++;
		}
		return it;
	}
	D& operator[](const T& key) {
		iterator it = find(key);
		if (it == end(it.index))
			emplace(key, D());
		return (*find(key)).elem;
	}
	D& operator[](T&& key) {
		iterator it = find(key);
		if (it == end(it.index))emplace(key, D());
		return (*find(key)).elem;
	}

	void insert(std::pair<T, D> p) {
		return emplace(p.first, p.second);
	}
	void emplace(T key,D elem) {
		int index = hash(key);
		iterator it = find(key);
		if (it != end(it.index)) return;
		table[index].push_front(pair(key,elem));
		size++;
		per_of_fill = (float)size / (float)capacity;
		if (per_of_fill >= 0.7f) 
			repack();
	}

	void erase(T key) {
		iterator elem = find(key);
		size_t index = hash(key);
		if (elem == end(index)) throw "Element not founded";
		table[index].erase(elem.it);
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
				ostream<< row.key << ":" << row.elem<<' ';
				flag = true;
			}
			if(flag)
			ostream << '\n';
		}
		return ostream;
	}
};