#pragma once
#include <vector>
#include <algorithm>

template <class T1, class T2>
class OrderedTable {
	std::vector<std::pair<T1, T2>> _data;

	class Comparator {
	public:
		bool operator()(const std::pair<T1, T2>& p1, const std::pair<T1, T2>& p2) const noexcept {
			return p1.first < p2.first;
		}
	};
public:
	class iterator {
		typename std::vector<std::pair<T1, T2>>::iterator _iterator;

		friend class OrderedTable;
	public:
		iterator() = delete;
		iterator(const typename std::vector<std::pair<T1, T2>>::iterator& iterator) : _iterator(iterator) {}
		iterator(const iterator& iterator) : _iterator(iterator._iterator) {}
		iterator& operator=(const iterator& it) {
			_iterator = it._iterator;
			return *this;
		}

		std::pair<T1, T2>& operator*() {
			return *_iterator;
		}
		iterator operator++() {
			++_iterator;
			return iterator(_iterator);
		}
		iterator operator++(int) {
			iterator result = *this;
			operator++();
			return result;
		}
		iterator operator--() {
			return iterator(--_iterator);
		}
		iterator operator--(int) {
			iterator result = *this;
			operator--();
			return result;
		}
		bool operator==(const iterator& iterator) {
			return _iterator == iterator._iterator;
		}
		bool operator!=(const iterator& iterator) {
			return _iterator != iterator._iterator;
		}
	};
	iterator begin() {
		return iterator(_data.begin());
	}
	iterator end() {
		return iterator(_data.end());
	}
	void insert(const std::pair<T1, T2>& row) {
		if (find(row.first) == end()) {
			Comparator comp;
			_data.insert(std::upper_bound(_data.begin(), _data.end(), row, comp), row);
		}
	}
	void emplace(const T1& key, const T2& data) {
		insert({ key, data });
	}
	void erase(const T1& key) {
		if (find(key) != end()) {
			Comparator comp;
			std::pair<T1, T2> pair(key, T2());
			_data.erase(std::lower_bound(_data.begin(), _data.end(), pair, comp));
		}
		else {
			throw std::exception("Out of the bounds");
		}
	}
	void erase(iterator it) {
		_data.erase(it._iterator);
	}
	iterator find(const T1& key) {
		Comparator comp;
		std::pair<T1, T2> pair(key, T2());
		auto it = std::lower_bound(_data.begin(), _data.end(), pair, comp);

		if (it == _data.end() || (*it).first != key) {
			return end();
		}
		return iterator(it);
	}
};