#ifndef _ZT_STRING_H_
#define _ZT_STRING_H_

#include "Allocator.h"
#include "Iterator.h"

namespace ztSTL {
	//string class
	class string {
		typedef char value_type;
		typedef char* iterator;
		typedef char& reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
	private:
		iterator start;	
		iterator end;
		iterator end_of_storage;
		typedef allocator<char> string_allocator;

	public:
		//string s1;	//默认初始化，s1是一个空串
		string() :start(0), end(0), end_of_storage(0) {}
		//string s2(s1);	//s2是s1的一个副本
		string(const string& str);
		//string s3(n,str)
		string(size_type n,value_type c);
		template <typename InputIterator>
		string(InputIterator first, InputIterator last);
		
		//string s2=s1;	//等价于s2(s1)
		string& operator=(const string& str) {

		}
	};
}
#endif