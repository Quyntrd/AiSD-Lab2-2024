#include <Map.cpp>

int main() {
	UnorderedMap<int, int> map(10);
	map.insert(353, 11);
	map.insert(3, 11);
	map.insert(3, 12);
	map.insert(35, 11);
	map.insert(53, 11);


	std::cout << map.search(2) << std::endl;
	std::cout << "___________________" << std::endl;
	std::cout << map.count(3) << std::endl;
	std::cout << "___________________" << std::endl;
	map.print();
	std::cout << "___________________" << std::endl;
	std::cout << map.erase(3) << std::endl;
	std::cout << "___________________" << std::endl;
	map.print();
	std::cout << "___________________" << std::endl;
	std::cout << map.size() << std::endl;
	std::cout << "___________________" << std::endl;
	map.insert(7, 5);
	map.insert(5, 5);
	map.insert(5, 5);
	map.print();
	std::cout << "___________________" << std::endl;
	UnorderedMap<int, int> map1(10, 0, 10);


	map1.print();
	return 0;
}