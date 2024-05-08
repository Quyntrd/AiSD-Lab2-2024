#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <random>

template<typename Key, typename Value>
class UnorderedMap {
	struct Node {
		Key key;
		Value value;
		bool isdeleted;

		Node(): key(), value(), isdeleted(false) {}
		Node(const Key& k, const Value& v, bool deleted = false): key(k), value(v), isdeleted(deleted){}
	};
	std::vector<Node> _table;
	size_t _size = 0;
	const float _loadfactor = 0.75; // Лоад фактор для изменения размера хеш-таблицы
	
	int hash(const Key& key) const {
		const float prime_number = (std::sqrt(5) - 1 / 2);
		unsigned long long hash_value = key * 28 * prime_number;
		return (hash_value) % _table.size();
	}

	void rehash() {
		std::vector<Node> new_table;
		new_table.resize(_table.size() * 1.75);
		_size = 0;
		std::swap(new_table, _table);
		for (const auto& node: new_table) {
			if (!node.isdeleted) insert(node.key, node.value);
		}
	}
	
public:
	UnorderedMap(const size_t size): _table(size, Node()) {}
	UnorderedMap(const UnorderedMap& other) {
		_table = other._table;
		_size = other._size;
	}
	UnorderedMap(const size_t size, int min, int max) : _table(size, Node()) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(min, max);
		for (size_t i = 0; i < size; ++i) {
			int key = dis(gen);
			int value = dis(gen);
			insert(key, value);
		}
	}
	UnorderedMap& operator=(const UnorderedMap& other) {
		if (this != &other) {
			_table = other._table;
		}
		return *this;
	}
	void print() const {
		for (const auto& node : _table) {
			if (node.value == 0 && node.key == 0) {
				std::cout << "Empty" << std::endl;
			}
			else if(!node.isdeleted) {
				std::cout << "Key: " << node.key << ", Value: " << node.value << std::endl;
 			}
		}
	}
	void insert(const Key& key, const Value& value) {
		if ((float)_size / (float)_table.size() >= _loadfactor) {
			rehash();
		}
		size_t idx = hash(key);
		_table[idx].key = key;
		_table[idx].value = value;
		_table[idx].isdeleted = false;
		++_size;
	}
	void insert_or_assign(const Key& key, const Value& value) {
		auto result = search(key);
		if (!result) {
			insert(key, value);
			return;
		}
		*result = value;
	}
	bool contains(const Value& value) const {
		for (const auto& node : _table) {
			if (!node.isdeleted && node.value == value) {
				return true;
			}
		}
		return false;
	}
	Value* search(const Key& key) {
		size_t idx = hash(key);
		size_t start = idx;
		do {
			if (_table[idx].key == key && !_table[idx].isdeleted) return &_table[idx].value;
			idx = (idx + 1) % _table.size();
		} while (idx != start);
		return nullptr;
	}
	bool erase(const Key& key) {
		size_t idx = hash(key);
		size_t start = idx;
		do {
			if (_table[idx].key == key && !_table[idx].isdeleted) {
				_table[idx].isdeleted = true;
				--_size;
				return true;
			}
			idx = (idx + 1) % _table.size();
		} while (idx != start);
		return false;
	}
	int count(const Key& key) const {
		size_t idx = hash(key);
		size_t start = idx;
		int count = 0;
		do {
			if (_table[idx].key == key && !_table[idx].isdeleted) ++count;
			idx = (idx + 1) % _table.size();
		} while (idx != start);
		return count;
	}
	size_t size() const {
		return _size;
	}
};