#ifndef _ZHVECTOR_H_
#define _ZHVECTOR_H_

#include "Allocator.h"
#include "Iterator.h"
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <initializer_list>
namespace ztSTL {
	/*vector的实现关键在于其对大小的控制以及重新配置时数据移动的效率*/
	template <class T>
	class vector {

	public:
		//vector的嵌套类型定义
		typedef T value_type;
		typedef T* pointer;
		typedef T* iterator;
		typedef T& reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		
	private:
		iterator start;	//目前使用的空间的头
		iterator finish;	//目前使用的空间的尾
		iterator end_of_storage; //目前可用空间的尾
		typedef allocator<T> vector_allocator;
	public:
		iterator begin() { return start; }
		iterator end() { return finish; }
		size_type size() { return static_cast<size_type>(end() - begin()); }
		bool empty() const { return (finish-start == 0); }
		size_type capacity() const { return static_cast<size_type>(end_of_storage - start); }
		reference operator [](size_type n) { return *(begin() + n); }
		reference front() { return *(begin()); }
		reference back() { return *(end() - 1); }

		//默认构造函数 vector<T> v1()
		vector() :start(0), finish(0), end_of_storage(0) {};

		//构造函数重载 vector<T> v2(n,t)
		vector(size_type n,const T& value){allocate_and_fill(n, value);}
		vector(int n, const T& value) {allocate_and_fill(n, value);}
		vector(long n, const T& value) {allocate_and_fill(n, value);}

		//构造函数重载 vector<T> v3(n)
		vector(size_type n) {allocate_and_fill(n, T());}
		vector(int n) {allocate_and_fill(n, T());}
		vector(long n) {allocate_and_fill(n, T());}

		//构造函数重载 vector<T> v4(v5)
		vector(const vector<T>& ivec) {
			start = allocate_and_copy(ivec.begin(),
				ivec.end(),ivec.end() - ivec.begin());
			finish = start + (ivec.end() - ivec.begin());
			end_of_storage = finish;
		}

		//构造函数重载 vector<T> v6(b,e)
		vector(const iterator& b, const iterator& e) {
			start = allocate_and_copy(b, e, size_type(e - b + 1));
			finish = start + (e - b + 1);
			end_of_storage = finish;
		}

		~vector() {
			vector_allocator::destroy(start, finish);
			vector_allocator::deallocate(start, end_of_storage - start);
		}

		//将元素插入到末尾
		void push_back(const T& value) {
			if (finish != end_of_storage) {
				vector_allocator::construct(finish, value);
				++finish;
			}else {
				//重新申请空间
				const size_type old_size = size();
				const size_type new_size = (old_size == 0) ? 1 : 2 * old_size;
				iterator new_start = vector_allocator::allocate(new_size,0);
				iterator new_finish = new_start;
				//内存的分配要有原子性：要么全部成功，要么全部失败
				try {
					//1.将原内容拷贝到新vector中
					//2.为新的元素设置初值
					//3.调整
					for (iterator it = begin(); it < end(); ++it) {
						vector_allocator::construct(new_finish++, *it);
					}
					vector_allocator::construct(new_finish, value);
					++new_finish;
				}
				catch (...) {
					//如果失败了
					vector_allocator::destroy(new_start, new_finish);//删除申请到的内存
					new_start = new_finish = nullptr;
					throw;

				}

				//析构并释放原vector
				vector_allocator::destroy(begin(), end());
				//删除内存
				free(start);
				//调整迭代器，指向新的vector
				start = new_start;
				finish = new_finish;
				end_of_storage = new_start + new_size;
			}
		}
		
		//将尾端元素删除，并调整大小
		void pop_back() {
			--finish;
			vector_allocator::destroy(finish);
		}

		//清除[first,last)之间所有的元素
		iterator erase(iterator first, iterator last) {
			//尾部残留对象数
			difference_type left_of_trail = end() - last;
			//删去的对象数目
			difference_type lenth_of_removed = last - first;
			finish = finish - lenth_of_removed;
			for (; left_of_trail != 0; --left_of_trail) {
				auto temp = last - lenth_of_removed;
				*temp = *(last++);
			}
			return first;
		}

		private:
			iterator allocate_and_copy(iterator first, iterator last, size_type n) {
				//分配空间，并复制值到空间中
				iterator ret = vector_allocator::allocate(n);
				iterator start = ret;
				if (ret) {
					while (n--) {
						vector_allocator::construct(ret, *first);
						++ret;
						++first;
					}
					std::cout << std::endl;
				}
				else {
					std::cerr << "Out of memory,program terminated" << std::endl;
					std::exit(0);
				}
			}

			//将first到last迭代器中间的元素拷贝到start开始的内存中
			iterator copy(iterator first, iterator last, iterator start) {
				while (fisrt < last) {
					*start++ = sirst++;
				}
				return start;
			}

			iterator allocate_and_fill(size_type n, const T& value) {
				//分配空间并填充初始值
				iterator ret = vector_allocator::allocate(n);
				//申请内存成功，在得到的内存上创建对象
				if (ret) {
					start = ret;
					end_of_storage = start + n;
					finish = end_of_storage;
					while (n--) {
						//在内存上一个一个地构造对象
						vector_allocator::construct(ret, value);
						++ret;
					}
				}
				else {
					std::cerr << "Out of memory,program terminated" << std::endl;
					std::exit(0);
				}
			}



	};
}
#endif



