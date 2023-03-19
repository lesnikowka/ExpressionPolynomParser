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
	class Iterator {
		typename std::vector<std::pair<T1, T2>>::iterator _iterator;

		friend class OrderedTable;
	public:
		Iterator() = delete;
		Iterator(const typename std::vector<std::pair<T1, T2>>::iterator& iterator) : _iterator(iterator) {}
		Iterator(const Iterator& iterator) : _iterator(iterator._iterator) {}
		Iterator& operator=(const Iterator& it) {
			_iterator = it._iterator;
			return *this;
		}

		std::pair<T1, T2>& operator*() {
			return *_iterator;
		}
		Iterator operator++() {
			return Iterator(++_iterator);
		}
		Iterator operator++(int) {
			Iterator result = *this;
			operator++();
			return result;
		}
		Iterator operator--() {
			return Iterator(--_iterator);
		}
		Iterator operator--(int) {
			Iterator result = *this;
			operator--();
			return result;
		}
		bool operator==(const Iterator& iterator) {
			return _iterator == iterator._iterator;
		}
		bool operator!=(const Iterator& iterator) {
			return _iterator != iterator._iterator;
		}
	};
	Iterator begin() {
		return Iterator(_data.begin());
	}
	Iterator end() {
		return Iterator(_data.end());
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
	void erase(Iterator it) {
		_data.erase(it._iterator);
	}
	Iterator find(const T1& key) {
		Comparator comp;
		std::pair<T1, T2> pair(key, T2());
		auto it = std::lower_bound(_data.begin(), _data.end(), pair, comp);

		if (it == _data.end() || (*it).first != key) {
			return end();
		}
		return Iterator(it);
	}
};