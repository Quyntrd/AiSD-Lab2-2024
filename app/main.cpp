#include <Map.cpp>

void count_same_numbers(const UnorderedMap<int, int>& map, int minValue, int maxValue) {
	for (int i = minValue; i <= maxValue; ++i) {
		if (map.count(i) > 1) {
			std::cout << "Number " << i << ", Count: " << map.count(i) << std::endl;
		}
	}
}

int main() {
	UnorderedMap<int, int> map(10);
	map.insert(353, 11);
	map.insert(3, 11);
	map.insert(3, 12);
	map.insert(35, 11);
	map.insert(53, 11);
	map.insert_or_assign(35, 34);
	std::cout << "Map Search of 2" << std::endl;
	std::cout << map.search(2) << std::endl;
	std::cout << "Map Search of 3" << std::endl;
	std::cout << *map.search(3) << std::endl;
	std::cout << "___________________" << std::endl;
	std::cout << "Map count of 3" << std::endl;
	std::cout << map.count(3) << std::endl;
	std::cout << "___________________" << std::endl;
	std::cout << "Map print" << std::endl;
	map.print();
	std::cout << "___________________" << std::endl;
	std::cout << "Map erase" << std::endl;
	std::cout << map.erase(35) << std::endl;
	std::cout << "___________________" << std::endl;
	std::cout << "Map print" << std::endl;
	map.print();
	std::cout << "___________________" << std::endl;
	std::cout << "Map size" << std::endl;
	std::cout << map.size() << std::endl;
	std::cout << "___________________" << std::endl;
	map.insert(7, 5);
	map.insert(5, 5);
	map.insert(5, 5);
	std::cout << "Map print" << std::endl;
	map.print();
	std::cout << "___________________" << std::endl;
	UnorderedMap<int, int> map1(10, 1, 5);
	std::cout << "Map1: " << std::endl;
	map1.print();
	std::cout << "___________________" << std::endl;
	std::cout << "Count same numbers" << std::endl;
	count_same_numbers(map1, 1, 100);
	UnorderedMap<char, char> mapchar(15, 1, 100);
	std::cout << "___________________" << std::endl;
	mapchar.print();
	UnorderedMap<int, std::string> mapstring(15);
	mapstring.insert(412, "One");
	std::cout << "___________________" << std::endl;
	mapstring.print();
	return 0;
}