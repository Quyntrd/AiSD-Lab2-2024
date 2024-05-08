#pragma once
#include <iostream>
#include <vector>
#include <list>
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
	const size_t _primenumber = 31; //Число для реализации мультапликативной схемы
	const float _loadfactor = 0.75; // Лоад фактор для изменения размеры хеш-таблицы
	
	size_t hash(const Key& key) const {
		return (_primenumber * key) % _table.size();
	}

	void rehash() {
		vector<Node> old = _table;
		_table.assign(_table.size() * 2, Node());

		for (const auto& node; old) {
			if (!node.isdeleted) insert(node.key, node.value);
		}
	}
	
public:
	UnorderedMap(size_t size): _table(size, Node()) {}
	UnorderedMap(const UnorderedMap& other) {
		_table = other._table;
	}
	UnorderedMap(size_t size, int min, int max) : _table(size, Node()) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis(min, max);
		for (size_t i = 0; i < count; ++i) {
			Key key = dis(gen);
			Value value = dis(gen);
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
			if (!node.isdeleted) {
				cout << "Key: " << node.key << ", Value: " << node.value << endl;
 			}
		}
	}
	void insert(const Key& key, const Value& value) {
		if ((float)size() / _table.size() >= _loadfactor) {
			rehash();
		}
		size_t idx = hash(key);
		while (!table[idx].isdeleted) {
			idx = (idx + 1) % _table.size();
		}
		_table[idx].key = key;
		_table[idx].value = value;
		_table[idx].isdeleted = false;
	}
	void insert_or_assign(const Key& key, const Value& value) {
		size_t idx = hash(key);
		while (!_table[idx].isdeleted && _table[idx].key != key) {
			idx = (idx + 1) % _table.size();
		}
		if (!_table[idx].isdeleted) {
			_table[idx].value = value;
		}
		else {
			_table[idx].key = key;
			_table[idx].value = value;
			_table[idx].isdeleted = false;
		}
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
		} while (index != start);
		return nullptr;
	}
	bool erase(const K& key) {
		size_t idx = hash(key);
		size_t start = idx;
		do {
			if (_table[idx].key == key && !_table[idx].isdeleted) {
				_table[idx].isdeleted = true;
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
			if (table[idx].key == key && !_table[idx].isdeleted) ++count;
			idx = (idx + 1) % _table.size();
		} while (idx != start);
		return count;
	}
	size_t size() const {
		return _table.size();
	}
};