#pragma once
#include <vector>
#include <algorithm>

template <class T1, class T2>
class OrderedTable {
public:
	class iterator {
		typename std::vector<std::pair<T1, T2>>::iterator _iterator;
		typename std::vector<std::pair<T1, T2>>::iterator _end;

		friend class OrderedTable;
	public:
		iterator() = delete;
		iterator(const typename std::vector<std::pair<T1, T2>>::iterator& iterator, 
			const typename std::vector<std::pair<T1, T2>>::iterator& end) : _iterator(iterator), _end(end) {}
		iterator(const iterator& iterator) : _iterator(iterator._iterator), _end(iterator._end) {}

		iterator& operator=(const iterator& it) {
			_iterator = it._iterator;
			_end = it._end;
			return *this;
		}

		std::pair<T1, T2> operator*() {
			if(_iterator == _end) throw std::exception("end iterator");
			return *_iterator;
		}

		iterator operator++() {
			if(_iterator == _end) throw std::exception("end iterator");
			++_iterator;
			return iterator(_iterator, _end);
		}

		iterator operator++(int) {
			iterator result = *this;
			operator++();
			return result;
		}

		bool operator==(const iterator& iterator) const{
			return _iterator == iterator._iterator;
		}

		bool operator!=(const iterator& iterator) const{
			return _iterator != iterator._iterator;
		}
	};

private:

	std::vector<std::pair<T1, T2>> _data;

	class Comparator {
	public:
		bool operator()(const std::pair<T1, T2>& p1, const std::pair<T1, T2>& p2) const noexcept {
			return p1.first < p2.first;
		}
	};

public:
	iterator begin() {
		return iterator(_data.begin(), _data.end());
	}
	iterator end() {
		return iterator(_data.end(), _data.end());
	}

	OrderedTable() = default;
	OrderedTable(const OrderedTable& o) = default;
	OrderedTable(OrderedTable&& o) { _data = std::move(o._data); }

	OrderedTable& operator=(const OrderedTable& o) = default;
	OrderedTable& operator=(OrderedTable&& o) {
		_data = std::move(o._data);
		return *this;
	}

	bool operator==(const OrderedTable& o) const {
		return _data == o._data;
	}

	bool operator!=(const OrderedTable& o) const {
		return !operator==(o);
	}

	size_t size() { return _data.size(); }

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
		return iterator(it, _data.end());
	}

	T2& operator[](const T1& key) {
		Comparator comp;
		std::pair<T1, T2> pair(key, T2());
		auto it = std::lower_bound(_data.begin(), _data.end(), pair, comp);

		if (it == _data.end()) {
			emplace(key, T2());
			it = std::lower_bound(_data.begin(), _data.end(), pair, comp);
		}
		return (*it).second;
	}
};