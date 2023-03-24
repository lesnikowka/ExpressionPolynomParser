#pragma once

#include <cmath>
#include <vector>


const size_t STANDART_CAPACITY = 101;
const size_t STANDART_STEP = 5;
const size_t MULTIPLIER = 21;

const double MAXIMUM_OCCUPANCY = 0.7;

template <typename T>
class HashTableOpenAdressing {
	struct Tuple {
		std::pair<std::string, T> key_val;

		bool was_used;
		bool is_deleted;

		Tuple() : was_used(false), is_deleted(false) {}
		Tuple(const Tuple& t) : key_val(t.key_val), was_used(t.was_used), is_deleted(t.is_deleted) {}

		Tuple& operator=(const Tuple& t) {
			key_val = t.key_val;
			was_used = t.was_used;
			is_deleted = t.is_deleted;
		}
	};

	std::vector<Tuple> _data;

	size_t _capacity;
	size_t _step;
	size_t _number_of_elements;
	

	bool is_simple(size_t number) {
		int i = 2;
		for (; i * i <= number; i++) 
			if (number % i == 0) return false;
		return true;
	}

	size_t make_simple(size_t number) {
		while (!is_simple(number))
			number--;

		return number;
	}

	size_t hash(const std::string& s) const {
		size_t hash_code = 0;

		for (char c : s) {
			hash_code += (size_t)c;
			hash_code += hash_code << 10;
			hash_code += hash_code >> 6;
		}

		hash_code += hash_code << 3;
		hash_code ^= hash_code >> 11;
		hash_code += hash_code << 15;

		return hash_code % _capacity;
	}

	void insert_in_vector(const std::pair<std::string, T>& key_val, size_t index, std::vector<Tuple>& data, size_t capacity, size_t step) {

		for (size_t num_of_passed_els = 0; num_of_passed_els <= capacity; index += step, num_of_passed_els++) {

			if (data[index].was_used == false) {

				data[index].key_val = key_val;
				data[index].was_used = true;

				break;
			}
		}
	}

	size_t change_step(size_t old_capacity, size_t new_capacity, size_t step) {
		return step * (new_capacity / old_capacity);
	}

	size_t change_capacity(size_t capacity) {
		return make_simple(capacity * MULTIPLIER);
	}

	void recomposing() {
		if ((double)_number_of_elements / _capacity < MAXIMUM_OCCUPANCY) return;


		size_t new_capacity = change_capacity(_capacity);
		size_t new_step = change_step(_capacity, new_capacity, _step);

		std::vector<Tuple> new_data(new_capacity);

		_capacity = new_capacity;
		_step = new_step;

		for (const auto& row : _data)
			if (!row.is_deleted && row.was_used) {
				size_t hash_code = hash(row.key_val.first);
				insert_in_vector(row.key_val, hash_code, new_data, new_capacity, new_step);
			}

		_data = std::move(new_data);
	}

public:
	class iterator {
		friend class HashTableOpenAdressing;

		std::vector<Tuple>* _data;

		size_t _index;

		bool _is_end;

	public:
		iterator(std::vector<Tuple>* data, size_t index, bool is_end) : _data(data), _index(index), _is_end(is_end) {}
		iterator(const iterator& it) : _data(it._data), _index(it._index), _is_end(it._is_end) {}
		iterator& operator=(const iterator& it) {
			_data = it._data;
			_index = it._index;
			_is_end = it._is_end;
		}

		T& operator*() {
			if (_is_end) throw std::exception("end iterator");

			return _data->operator[](_index).key_val.second;
		}

		bool operator==(const iterator& it) const {
			if (it._index == _index && !(it._is_end ^ _is_end) || (it._is_end && _is_end))  return true;
			return false;
		}

		bool operator!=(const iterator& it) const{
			return !operator==(it);
		}

		iterator& operator++() {
			if (_is_end) throw std::exception("end iterator");

			size_t index = _index;

			bool a = _data->operator[](index).was_used;
			bool b = _data->operator[](index).is_deleted;

			while (index < _data->size() && ((_data->operator[](index).is_deleted || !_data->operator[](index).was_used) || index == _index)) {
				index++;
			}

			if (index == _data->size()) {
				_is_end = true;
			}

			_index = index;

			return *this;	
		}

		iterator operator++(int) {
			iterator result(*this);

			operator++();

			return result;
		}
	};

	iterator begin() const{
		iterator it(&_data, 0, false);
		
		if (_number_of_elements == 0) {
			it._is_end = true;
		}
		else if (!_data[0].was_used || _data[0].is_deleted) {
			++it;
		}

		return it;
	}

	iterator end() const{
		return iterator(&_data, 0, true);
	}


	HashTableOpenAdressing() : _capacity(STANDART_CAPACITY), _step(STANDART_STEP), _number_of_elements(0) {
		_data = std::vector<Tuple>(STANDART_CAPACITY);
	}

	HashTableOpenAdressing(const HashTableOpenAdressing& ht) : _capacity(ht._capacity), _step(ht._step), _data(ht._data), _number_of_elements(ht._number_of_elements) {}

	HashTableOpenAdressing(HashTableOpenAdressing&& ht) : _capacity(ht._capacity), _step(ht._step), _data(std::move(ht._data)), _number_of_elements(ht._number_of_elements) {}

	HashTableOpenAdressing& operator=(const HashTableOpenAdressing& ht) {
		_capacity = ht._capacity;
		_step = ht._step;
		_data = ht._data;
		_number_of_elements = ht._number_of_elements;
	}

	HashTableOpenAdressing& operator=(HashTableOpenAdressing&& ht) {
		_capacity = ht._capacity;
		_step = ht._step;
		_data = std::move(ht._data);
		_number_of_elements = ht._number_of_elements;
	}

	size_t capacity() const noexcept{ return _capacity; }
	size_t step() const noexcept { return _step; }
	size_t size() const noexcept { return _number_of_elements; }

	void emplace(const std::string& key, const T& value) {
		insert(std::make_pair(key, value));
	}

	void insert(const std::pair<std::string, T>& key_value) {
		recomposing();

		size_t hash_code = hash(key_value.first);

		insert_in_vector(key_value, hash_code, _data, _capacity, _step);

		_number_of_elements++;
	}

	void erase(const std::string& key) {
		size_t index = hash(key), cropped_index;

		for (size_t num_of_passed_els = 0; num_of_passed_els <= _capacity; index += _step, num_of_passed_els++) {

			if (_data[index].key_val.first == key) {

				_data[index].is_deleted = true;

				_number_of_elements--;

				return;
			}
		}

		throw std::exception("element is not found");
	}

	iterator find(const std::string& key) const {
		size_t index = hash(key), cropped_index;

		for (size_t num_of_passed_els = 0; num_of_passed_els <= _capacity; index += _step, num_of_passed_els++) {
			if (!_data[index].was_used) break;

			if (_data[index].key_val.first == key && !_data[index].is_deleted) {
				return iterator(&_data, index, false);
			}
		}
		return iterator(&data, 0, true);
	}
};