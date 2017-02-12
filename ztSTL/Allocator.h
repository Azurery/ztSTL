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
		/*���ÿռ䣬���Դ���n��T����
		�ڶ�����������ʾ��ʵ���Ͽ��ܻ������������������ԣ�
		����ȫ������*/
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
		//���ؿɳɹ����õ����ֵ
		size_type max_size() const {
			return size_type(UINT_MAX/sizeof(T));
		}

		//����ĳ������ĵ�ַ
		//a.address(r)��ͬ��&r
		pointer address(reference r) {
			return (pointer)&r;
		}

		//����ĳ��const����ĵ�ַ
		const_pointer const_adress(const_pointer r) {
			return (const_pointer)&x;
		}
	};
	*/
}

#endif
