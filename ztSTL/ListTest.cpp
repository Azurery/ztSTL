//#include "List.h"
//#include <iostream>
//#include <cassert>
//
//int main() {
//	ztSTL::list<int> li;
//	for (int i = 5; i <  11; ++i) {
//		li.push_back(i);
//	}
//	//li.insert(li.end(), 11);
//	//li.push_front(10);
//	//li.pop_back();
//	for (auto beg = li.begin(); beg != li.end(); ++beg) {
//		std::cout << *beg << std::endl;
//	}
//	std::cout << "- - - - - - - - - -  - - -  - - - - - - -" << std::endl;
//	//li.insert(li.end(), 11);
//	//li.erase(li.begin());
//	//li.erase(li.begin(), li.end());
//	//li.pop_back();
//	li.clear();
//	for (auto beg = li.begin(); beg != li.end(); ++beg) {
//		std::cout << *beg << std::endl;
//	}
//	std::cout << "size(): " << li.size() << std::endl;
//	std::cout << "front(): " << li.front() << std::endl;
//	//std::cout << "back(): " << li.back() << std::endl;
//	std::cout << "empty(): " << li.empty() << std::endl;
//	system("pause");
//
//	return 0;
//}