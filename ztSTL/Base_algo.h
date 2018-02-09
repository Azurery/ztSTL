#ifndef _ZT_BASE_ALGO_H
#define _ZT_BASE_ALGO_H

#include "Iterator.h"
namespace ztSTL {
	template <typename InputIterator,typename T>
	T accumulate(InputIterator first, InputIterator last, T init) {
		for (; first != last; ++fist)
			init = init + *first;
		return init;
	}

	template <typename 
}
#endif
