#pragma once

#include <cmath>
#include <vector>


const size_t STANDART_CAPACITY = 128;
const size_t STANDART_STEP = 5;
const size_t MULTIPLIER = 8;

const double MAXIMUM_OCCUPANCY = 0.7;

template <class Y, class T>
class HashTableOpenAdressing {
private:
	struct Tuple {
		std::pair<Y, T> key_val;

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
public:
	class iterator {
		friend class HashTableOpenAdressing;

		std::vector<Tuple>* _data;

		size_t _index;

	public:
		iterator() = delete;
		iterator(typename std::vector<Tuple>* data, size_t index) : _data(data), _index(index) {}
		iterator(const iterator& it) : _data(it._data), _index(it._index) {}
		iterator& operator=(const iterator& it) {
			_data = it._data;
			_index = it._index;
			return *this;
		}

		std::pair<std::string, T> operator*() {
			if (_index == _data->size()) throw std::exception("end iterator");

			return _data->operator[](_index).key_val;
		}

		bool operator==(const iterator& it) const {
			if (_data != it._data) throw std::exception("iterators from different tables");

			return (_index == it._index);
		}

		bool operator!=(const iterator& it) const {
			return !operator==(it);
		}

		iterator& operator++() {
			if (_index == _data->size()) throw std::exception("end iterator");

			size_t index = _index;

			bool a = _data->operator[](index).was_used;
			bool b = _data->operator[](index).is_deleted;

			while (index < _data->size() && ((_data->operator[](index).is_deleted || !_data->operator[](index).was_used) || index == _index)) {
				index++;
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

private:

	std::vector<Tuple> _data;

	size_t _capacity;
	size_t _step;
	size_t _number_of_elements;

	std::pair<size_t, size_t> shift;


	void insert_in_vector(const std::pair<Y, T>& key_val, size_t index, std::vector<Tuple>& data, size_t capacity, size_t step) {

		for (size_t num_of_passed_els = 0; num_of_passed_els <= capacity; index = crop_index(index + step), num_of_passed_els++) {

			if (data[index].was_used == false) {

				data[index].key_val = key_val;
				data[index].was_used = true;

				break;
			}
		}
	}

	size_t crop_index(size_t index) {
		return index & (_capacity - 1);
	}

	size_t change_step(size_t old_capacity, size_t new_capacity, size_t step) {
		size_t new_step = step * (new_capacity / old_capacity);

		if (new_step & 1 == 0) new_step--;

		return new_step;
	}

	size_t change_capacity(size_t capacity) {
		return capacity * MULTIPLIER;
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
				size_t hash_code = hash(row.key_val.first, shift);
				insert_in_vector(row.key_val, hash_code, new_data, new_capacity, new_step);
			}

		_data = std::move(new_data);
	}

public:


	iterator begin() {
		iterator it(&_data, 0);

		if (_number_of_elements == 0) {
			it._index = _data.size();
		}
		else if (!_data[0].was_used || _data[0].is_deleted) {
			++it;
		}

		return it;
	}

	iterator end() {
		return iterator(&_data, _data.size());
	}


	HashTableOpenAdressing() : _capacity(STANDART_CAPACITY), _step(STANDART_STEP), _number_of_elements(0) {
		_data = std::vector<Tuple>(STANDART_CAPACITY);
		std::srand(std::time(nullptr));
		shift.first = std::rand() % 100;
		shift.second = std::rand() % 100;
	}

	HashTableOpenAdressing(const HashTableOpenAdressing& ht) : _capacity(ht._capacity), _step(ht._step), 
		_data(ht._data), _number_of_elements(ht._number_of_elements), shift(ht.shift) {}

	HashTableOpenAdressing(HashTableOpenAdressing&& ht) : _capacity(ht._capacity), _step(ht._step), _data(std::move(ht._data)), 
		_number_of_elements(ht._number_of_elements), shift(ht.shift) {}

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

	size_t capacity() const noexcept { return _capacity; }
	size_t step() const noexcept { return _step; }
	size_t size() const noexcept { return _number_of_elements; }

	void emplace(const Y& key, const T& value) {
		insert(std::make_pair(key, value));
	}

	void insert(const std::pair<Y, T>& key_value) {
		recomposing();

		size_t hash_code = crop_index(hash(key_value.first, shift));

		insert_in_vector(key_value, hash_code, _data, _capacity, _step);

		_number_of_elements++;
	}

	void erase(const Y& key) {
		size_t index = crop_index(hash(key, shift));

		for (size_t num_of_passed_els = 0; num_of_passed_els <= _capacity; index = crop_index(index + _step), num_of_passed_els++) {

			if (_data[index].key_val.first == key) {

				_data[index].is_deleted = true;

				_number_of_elements--;

				return;
			}
		}

		throw std::exception("element is not found");
	}

	iterator find(const Y& key) const {
		size_t index = crop_index(hash(key), shift);

		for (size_t num_of_passed_els = 0; num_of_passed_els <= _capacity; crop_index(index + _step), num_of_passed_els++) {
			if (!_data[index].was_used) break;

			if (_data[index].key_val.first == key && !_data[index].is_deleted) {
				return iterator(&_data, index, false);
			}
		}
		return iterator(&_data, 0, true);
	}
};

template<class A>
size_t hash(const A& key, const std::pair<size_t, size_t>& shift) {
	return key.hash();
}


template<>
size_t hash<std::string>(const std::string& key, const std::pair<size_t, size_t>& shift) {
	size_t hash_code = 0;

	for (char c : key) {
		hash_code += (size_t)c;
		hash_code += hash_code << 10;
		hash_code += hash_code >> 6;
	}

	hash_code += hash_code << 3;
	hash_code ^= hash_code >> 11;
	hash_code += hash_code << 15;

	return hash_code * shift.first + shift.second;
}

//template<>
//size_t hash<int>(const int& key) {
//	
//}