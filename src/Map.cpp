#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <random>

using namespace std;

template<typename Key, typename Value>
class UnorderedMap {
	struct Pair {
		Key key;
		Value value;
		Pair() : key(), value() {};
		Pair(const Key& ke, const Value& val) : key(ke), value(val) {};
	};
	vector<Pair> _data;
	size_t _size;
	size_t hash(const Key& key) const {
		const int w = sizeof(size_t) * 8;
		size_t a = 2654435761;
		return (key * a % (1 << w) >> (w / 2);
	}
};