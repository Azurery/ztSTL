//#include <iostream>
//#include "vector.h"
////vector的不足之处：size（）函数
//
//int main() {
//	
//	ztstl::vector<int> ivec;
//	ivec.push_back(0);
//	ivec.push_back(1);
//	ivec.push_back(2);
//	ivec.push_back(3);
//	ivec.push_back(4);
//	//ivec.pop_back();
//	ivec.erase(ivec.begin(),ivec.end());
//	for (auto beg = ivec.begin(); beg != ivec.end(); ++beg) {
//		std::cout << *beg << std::endl;
//	}
//	std::cout << "begin(): "<<*(ivec.begin()) << std::endl;
//	std::cout <<"end(): "<< *(ivec.end()) << std::endl;
//	std::cout << "capacity(): "<<ivec.capacity() << std::endl;
//	std::cout <<"size(): "<< *(ivec.end()) << std::endl;
//	std::cout << ivec.empty() << std::endl;
//	system("pause");
//	return 0;
//}
