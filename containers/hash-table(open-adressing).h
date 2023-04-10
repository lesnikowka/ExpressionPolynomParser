#pragma once

#include<ctime>
#include <cmath>
#include <vector>


const std::vector<size_t> SIMPLE_NUMBERS_FOR_CAPACITY = { 101 ,197,397,797,1597,3203,6421,12853,25717,51437,102877,205759,411527,823117,1646237 };
const std::vector<size_t> STEPS_FOR_LINEAR_PROBING = { 5, 10, 20, 40, 80, 160, 320, 640, 1280, 2560, 5120, 10240, 20480, 40960, 81920 };

const double MAXIMUM_OCCUPANCY = 0.5;

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

		std::pair<Y, T> operator*() {
			if (_index == _data->size()) throw std::exception("end iterator");

			return (*_data)[_index].key_val;
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

			bool a = (*_data)[index].was_used;
			bool b = (*_data)[index].is_deleted;

			while (index < _data->size() && (((*_data)[index].is_deleted || !(*_data)[index].was_used) || index == _index)) {
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
	size_t _number_of_repacking;

	std::pair<size_t, size_t> shift;


	void insert_in_vector(const std::pair<Y, T>& key_val, size_t index, std::vector<Tuple>& data) {

		for (size_t num_of_passed_els = 0; num_of_passed_els <= _capacity; index = crop_index(index + _step), num_of_passed_els++) {
			if (data[index].was_used && data[index].key_val.first == key_val.first) break;
			if (data[index].was_used == false) {

				data[index].key_val = key_val;
				data[index].was_used = true;

				break;
			}
		}
	}

	size_t crop_index(size_t index) const{
		return index % _capacity;
	}

	void change_capacity_and_step() {
		_number_of_repacking++;
		_capacity = SIMPLE_NUMBERS_FOR_CAPACITY[_number_of_repacking];
		_step = STEPS_FOR_LINEAR_PROBING[_number_of_repacking];
	}

	void recomposing() {
		if ((double)_number_of_elements / _capacity < MAXIMUM_OCCUPANCY) return;

		change_capacity_and_step();

		std::vector<Tuple> new_data(_capacity);

		for (const auto& row : _data)
			if (!row.is_deleted && row.was_used) {
				insert_in_vector(row.key_val, crop_index(hash(row.key_val.first, shift)), new_data);
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


	HashTableOpenAdressing() : _number_of_elements(0), _number_of_repacking(0) {
		_capacity = SIMPLE_NUMBERS_FOR_CAPACITY[_number_of_repacking];
		_step = STEPS_FOR_LINEAR_PROBING[_number_of_repacking];
		_data = std::vector<Tuple>(_capacity);
		std::srand(std::time(nullptr));
		shift.first = std::rand() % 100;
		shift.second = std::rand() % 100;
	}

	HashTableOpenAdressing(const HashTableOpenAdressing& ht) : _capacity(ht._capacity), _step(ht._step), 
		_data(ht._data), _number_of_elements(ht._number_of_elements), shift(ht.shift), _number_of_repacking(ht._number_of_repacking) {}

	HashTableOpenAdressing(HashTableOpenAdressing&& ht) : _capacity(ht._capacity), _step(ht._step), _data(std::move(ht._data)), 
		_number_of_elements(ht._number_of_elements), shift(ht.shift), _number_of_repacking(ht._number_of_repacking) {}

	HashTableOpenAdressing& operator=(const HashTableOpenAdressing& ht) {
		_capacity = ht._capacity;
		_step = ht._step;
		_data = ht._data;
		_number_of_elements = ht._number_of_elements;
		shift = ht.shift;
		_number_of_repacking = ht._number_of_repacking();
	}

	HashTableOpenAdressing& operator=(HashTableOpenAdressing&& ht) {
		_capacity = ht._capacity;
		_step = ht._step;
		_data = std::move(ht._data);
		_number_of_elements = ht._number_of_elements;
		shift = ht.shift;
		_number_of_repacking = ht._number_of_repacking();
	}

	size_t capacity() const noexcept { return _capacity; }
	size_t size() const noexcept { return _number_of_elements; }

	void emplace(const Y& key, const T& value) {
		insert(std::make_pair(key, value));
	}

	void insert(const std::pair<Y, T>& key_value) {
		recomposing();

		insert_in_vector(key_value, crop_index(hash(key_value.first, shift)), _data);

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

	iterator find(const Y& key) {
		size_t index = crop_index(hash(key, shift));

		for (size_t num_of_passed_els = 0; num_of_passed_els <= _capacity; index = crop_index(index + _step), num_of_passed_els++) {
			if (!_data[index].was_used) break;

			if (_data[index].key_val.first == key && !_data[index].is_deleted) {
				return iterator(&_data, index);
			}
		}
		return iterator(&_data, _data.size());
	}

	T& operator[](const Y& key) {
		size_t index = crop_index(hash(key, shift));
		
		for (size_t num_of_passed_els = 0; num_of_passed_els <= _capacity; index = crop_index(index + _step), num_of_passed_els++) {
			if (!_data[index].was_used) {
				_data[index].key_val = { key, T() };
				_data[index].was_used = true;
				_number_of_elements++;
				break;
			}
			if (_data[index].key_val.first == key && !_data[index].is_deleted) {
				break;
			}
		}

		return _data[index].key_val.second;
	}

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

};

