#ifndef _ZT_SKIPLIST_H_
#define _ZT_SKIPLIST_H_
#include "Iterator.h"
namespace ztSTL {
	template <typename Key,typename Comparator>
	struct skiplist {
	private:
		struct Node;
		explicit skiplist(Comparator cmp, MemoryPool* mp);
		void insert(cosnt Key& key);
		void contains(const Key& key);
	};

	template <typename T>
	class skip_iterator :public iterator<forward_iterator_tag, T> {
		typedef const T* pointer;
		typedef const T& reference;
	};
}
#endif