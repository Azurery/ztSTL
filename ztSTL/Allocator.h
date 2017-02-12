#ifndef _ZT_ALLOCATOR_H_
#define _ZT_ALLOCATOR_H_
#include <cstdlib>
#include <new>
#include <cstddef>
#include <iostream>
#include <climits>

namespace ztSTL {
	template <typename T>
	class allocator {
	public:
		typedef T			value_type;
		typedef T*			pointer;
		typedef const T*	const_pointer;
		typedef T&			reference;
		typedef const T&	const_reference;
		typedef size_t		size_type;
		typedef ptrdiff_t	difference_type;

	public:
		static pointer allocate();
		static pointer allocate(size_type n);
		static void deallocate(pointer ptr);
		static void deallocate(pointer ptr, size_type n);

		static void construct(pointer ptr);
		static void construct(pointer ptr, const reference value);
		static void destroy(pointer ptr);
		static void destroy(pointer first, pointer last);
	};
		/*配置空间，足以储存n个T对象。
		第二个对象是提示，实现上可能会利用它来增加区域性，
		或完全忽略它*/
		/*allocate*/
		template <typename T>
		T* allocator<T>::allocate() {
			return allocate(sizeof(T));
		}
		template<typename T>
		T* allocator<T>::allocate(size_type n) {
			T* tmp = (T*)(::operator new((size_type)(n*sizeof(T))));
			return tmp;
		}
		/*construct*/
		template <typename T>
		void allocator<T>::construct(pointer p) {
			new(p)T();
		}
		template<typename T>
		void allocator<T>::construct(pointer p, const reference value) {
			new(p)T(value);
		}
		/*destroy*/
		template<typename T>
		void allocator<T>::destroy(pointer p) {
			p->~T();
		}
		template<typename T>
		void allocator<T>::destroy(pointer first,pointer last){
			for (; first != last; ++first) {
				first->~T();
			}
		}
		
		/*deallocate*/
		template <typename T>
		void allocator<T>::deallocate(pointer p) {
			::operator delete(p);
		}
		template<typename T>
		void allocator<T>::deallocate(pointer p, size_type n) {
			::operator delete(p);
		}
/*
		//返回可成功配置的最大值
		size_type max_size() const {
			return size_type(UINT_MAX/sizeof(T));
		}

		//返回某个对象的地址
		//a.address(r)等同于&r
		pointer address(reference r) {
			return (pointer)&r;
		}

		//返回某个const对象的地址
		const_pointer const_adress(const_pointer r) {
			return (const_pointer)&x;
		}
	};
	*/
}

#endif
