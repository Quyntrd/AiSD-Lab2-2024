#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <list>
template<typename Key, typename Value, template<typename...> class Container = std::list>
class UnorderedMap {
	struct Node {
		Key key;
		Value value;
		Node(): key(), value() {}
		Node(const Key& k, const Value& v, bool deleted = false): key(k), value(v){}
	};
	std::vector<Container<Node>> _table;
	size_t _size = 0;
	const float _loadfactor = 0.75; // Лоад фактор для изменения размера хеш-таблицы
	
	int hash(const Key& key) const {
		const float prime_number = (std::sqrt(5) - 1 / 2);
		unsigned long long hash_value = key * 28 * prime_number;
		return (hash_value) % _table.size();
	}

	void rehash() {
		std::vector<Container<Node>> new_table;
		new_table.resize(_table.size() * 1.75);
		_size = 0;
		std::swap(new_table, _table);
		for (size_t i = 0; i < new_table.size(); ++i) {
			for (auto& node : new_table[i]) {
				insert(node.key, node.value);
			}
		}
	}
	
public:
	UnorderedMap(const size_t size): _table(size) {}
	UnorderedMap(const UnorderedMap& other) {
		_table = other._table;
		_size = other._size;
	}
	UnorderedMap(const size_t size, const Key& min, const Value& max) : _table(size) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<size_t> dis(min, max);
		for (size_t i = 0; i < size; ++i) {
			Key key = (Key)dis(gen);
			Value value = (Value)dis(gen);
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
		for (const auto& list : _table) {
			for (auto& node: list){
				std::cout << "Key: " << node.key << ", Value: " << node.value << std::endl;
			}
		}
	}
	void insert(const Key& key, const Value& value) {
		if ((float)_size / (float)_table.size() >= _loadfactor) {
			rehash();
		}
		size_t idx = hash(key);
		_table[idx].emplace_back(key, value);
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
		for (auto& list : _table) {
			for (auto& node : list) {
				if (node.value == value) return true;
			}
		}
			
		return false;
	}
	Value* search(const Key& key) {
		size_t idx = hash(key);
		for (auto& node : _table[idx]) if (node.key == key) return &node.value;
		return nullptr;
	}
	bool erase(const Key& key) {
		size_t idx = hash(key);
		auto& list = _table[idx];
		for (auto it = list.begin(); it != list.end(); ++it) {
			if (it->key == key) {
				list.erase(it);
				--_size;
				return true;
			}
		}
		return false;
	}
	int count(const Key& key) const {
		size_t idx = hash(key);
		int count = 0;
		for (auto& node : _table[idx]) {
			if (node.key == key) ++count;
		}
		return count;
	}
	size_t size() const {
		return _size;
	}
};