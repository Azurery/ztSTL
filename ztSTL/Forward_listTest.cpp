//#include "Forward_list.h"
//#include <iostream>
//
//int main() {
//	ztSTL::forward_list<int> fl;
//	for (int i = 5; i<=10; ++i) {
//		fl.push_front(i);
//	}
//	for (auto beg = fl.begin(); beg != fl.end(); ++beg) {
//		std::cout << *beg << std::endl;
//	}
//	//fl.pop_front();
//	std::cout << "- - - - - - - - - - - -" << std::endl;
//	fl.reverse();
//	for (auto beg = fl.begin(); beg != fl.end(); ++beg) {
//		std::cout << *beg << std::endl;
//	}
//	//std::cout << "begin(): " << *(fl.begin()) << std::endl;
//	//std::cout << "front(): " << fl.front() << std::endl;
//	//std::cout << "end(): " << *(fl.end()) << std::endl;
//	//std::cout << "empty(): " << fl.empty() << std::endl;
//	std::cout << "size(): " << fl.size() << std::endl;
//	
//	system("pause");
//}