#pragma once

#include <cmath>
#include <vector>

const size_t STANDART_CAPACITY = 100;
const size_t STANDART_STEP = 3;
const size_t SIMPLE_NUMBER_FOR_HASH = 3;

const double MAXIMUM_OCCUPANCY = 0.7;

template <typename T>
class HashTable {
	struct Tuple {
		std::string key;

		T value;

		bool was_used;
		bool is_deleted;

		Tuple() : key(""), value(T()), was_used(false), is_deleted(false) {}
		Tuple(const Tuple& t) : key(t.key), value(t.value), was_used(t.was_used), is_deleted(t.is_deleted) {}

		Tuple& operator=(const Tuple& t) {
			key = t.key;
			value = t.value;
			was_used = t.was_used;
			is_deleted = t.is_deleted;
		}
	};

	std::vector<Tuple> _data;

	size_t _capacity;
	size_t _step;
	size_t _number_of_elements;

	size_t hash(const std::string& s) const {
		size_t hash_code = 0;

		for (size_t i = 0; i < s.size(); i++)
			hash_code += (size_t)s[i] * pow(SIMPLE_NUMBER_FOR_HASH, i);

		return hash_code;
	}

	void recomposing() {
		if ((double)_number_of_elements / _capacity < MAXIMUM_OCCUPANCY) return;


	}

public:
	HashTable() : _capacity(STANDART_CAPACITY), _step(STANDART_STEP), _number_of_elements(0) {
		_data = std::vector<Tuple>(STANDART_CAPACITY);
	}

	HashTable(const HashTable& ht) : _capacity(ht._capacity), _step(ht._step), _data(ht._data), _number_of_elements(ht._number_of_elements) {}

	HashTable& operator=(const HashTable& ht) {
		_capacity = ht._capacity;
		_step = ht._step;
		_data = ht._data;
		_number_of_elements = ht._number_of_elements;
	}

	size_t capacity() { return _capacity; }
	size_t step() { return _step; }
	size_t size() { return _number_of_elements; }

	void insert(std::pair<std::string, T> key_value) {
		size_t index = hash(key_value.first)% _capacity, cropped_index;

		for (size_t num_of_passed_els = 0; num_of_passed_els <= _capacity; index += _step, num_of_passed_els++) {
			cropped_index = index % _capacity;

			if (_data[cropped_index].was_used == false) {

				_data[cropped_index].key = key_value.first;
				_data[cropped_index].value = key_value.second;
				_data[cropped_index].was_used = true;

				break;
			}
		}
	}

	void erase(const std::string& key) {
		size_t index = hash(key_value.first) % _capacity, cropped_index;

		for (size_t num_of_passed_els = 0; num_of_passed_els <= _capacity; index += _step, num_of_passed_els++) {
			cropped_index = index % _capacity;

			if (_data[cropped_index].key == key) {

				_data[cropped_index].is_deleted = true;

				return;
			}
		}

		throw std::exception("element is not found");
	}

	T& find(const std::string& key) {
		size_t index = hash(key) % _capacity, cropped_index;

		for (size_t num_of_passed_els = 0; num_of_passed_els <= _capacity; index += _step, num_of_passed_els++) {
			cropped_index = index % _capacity;

			if (_data[cropped_index].key == key) {

				return _data[cropped_index].value;
			}
		}
	}
};