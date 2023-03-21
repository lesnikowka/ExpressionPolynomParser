#pragma once

#include <cmath>
#include <vector>

const size_t STANDART_CAPACITY = 101;
const size_t STANDART_STEP = 5;
const size_t MULTIPLIER = 21;

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

	void insert_in_vector(const std::string& key, const T& value, std::vector<Tuple>& data, size_t capacity, size_t step) {
		size_t index = hash(key), cropped_index;

		for (size_t num_of_passed_els = 0; num_of_passed_els <= capacity; index += step, num_of_passed_els++) {
			cropped_index = index % capacity;

			if (data[cropped_index].was_used == false) {

				data[cropped_index].key = key;
				data[cropped_index].value = value;
				data[cropped_index].was_used = true;

				break;
			}
		}
	}

	size_t change_step(size_t new_capacity) {
		return STANDART_STEP;
	}

	size_t change_capacity(size_t capacity) {
		return make_simple(capacity * MULTIPLIER);
	}

	void recomposing() {
		if ((double)_number_of_elements / _capacity < MAXIMUM_OCCUPANCY) return;
		
		size_t new_capacity = change_capacity(_capacity);
		size_t new_step = change_step(new_capacity);

		std::vector<Tuple> new_data(new_capacity);

		_capacity = new_capacity;
		_step = new_step;

		for (const auto& row : _data)
			if (!row.is_deleted && row.was_used)
				insert_in_vector(row.key, row.value, new_data, new_capacity, new_step);

		_data = std::move(new_data);
	}

public:
	HashTable() : _capacity(STANDART_CAPACITY), _step(STANDART_STEP), _number_of_elements(0) {
		_data = std::vector<Tuple>(STANDART_CAPACITY);
	}

	HashTable(const HashTable& ht) : _capacity(ht._capacity), _step(ht._step), _data(ht._data), _number_of_elements(ht._number_of_elements) {}

	HashTable(HashTable&& ht) : _capacity(ht._capacity), _step(ht._step), _data(std::move(ht._data)), _number_of_elements(ht._number_of_elements) {}

	HashTable& operator=(const HashTable& ht) {
		_capacity = ht._capacity;
		_step = ht._step;
		_data = ht._data;
		_number_of_elements = ht._number_of_elements;
	}

	HashTable& operator=(HashTable&& ht) {
		_capacity = ht._capacity;
		_step = ht._step;
		_data = std::move(ht._data);
		_number_of_elements = ht._number_of_elements;
	}

	size_t capacity() { return _capacity; }
	size_t step() { return _step; }
	size_t size() { return _number_of_elements; }

	void emplace(const std::string& key, const T& value) {
		recomposing();

		insert_in_vector(key, value, _data, _capacity, _step);

		_number_of_elements++;
	}

	void insert(const std::pair<std::string, T>& key_value) {
		emplace(key_value.first, key_value.second);
	}

	void erase(const std::string& key) {
		size_t index = hash(key_value.first), cropped_index;

		for (size_t num_of_passed_els = 0; num_of_passed_els <= _capacity; index += _step, num_of_passed_els++) {
			cropped_index = index % _capacity;

			if (_data[cropped_index].key == key) {

				_data[cropped_index].is_deleted = true;

				_number_of_elements--;

				return;
			}
		}

		throw std::exception("element is not found");
	}

	T& find(const std::string& key) {
		size_t index = hash(key), cropped_index;

		for (size_t num_of_passed_els = 0; num_of_passed_els <= _capacity; index += _step, num_of_passed_els++) {
			cropped_index = index % _capacity;

			if (_data[cropped_index].key == key) {

				return _data[cropped_index].value;
			}
		}
	}
};