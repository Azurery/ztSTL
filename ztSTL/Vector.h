#ifndef _ZHVECTOR_H_
#define _ZHVECTOR_H_

#include "Allocator.h"
#include "Iterator.h"
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <initializer_list>
namespace ztSTL {
	/*vector��ʵ�ֹؼ�������Դ�С�Ŀ����Լ���������ʱ�����ƶ���Ч��*/
	template <class T>
	class vector {

	public:
		//vector��Ƕ�����Ͷ���
		typedef T value_type;
		typedef T* pointer;
		typedef T* iterator;
		typedef T& reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		
	private:
		iterator start;	//Ŀǰʹ�õĿռ��ͷ
		iterator finish;	//Ŀǰʹ�õĿռ��β
		iterator end_of_storage; //Ŀǰ���ÿռ��β
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

		//Ĭ�Ϲ��캯�� vector<T> v1()
		vector() :start(0), finish(0), end_of_storage(0) {};

		//���캯������ vector<T> v2(n,t)
		vector(size_type n,const T& value){allocate_and_fill(n, value);}
		vector(int n, const T& value) {allocate_and_fill(n, value);}
		vector(long n, const T& value) {allocate_and_fill(n, value);}

		//���캯������ vector<T> v3(n)
		vector(size_type n) {allocate_and_fill(n, T());}
		vector(int n) {allocate_and_fill(n, T());}
		vector(long n) {allocate_and_fill(n, T());}

		//���캯������ vector<T> v4(v5)
		vector(const vector<T>& ivec) {
			start = allocate_and_copy(ivec.begin(),
				ivec.end(),ivec.end() - ivec.begin());
			finish = start + (ivec.end() - ivec.begin());
			end_of_storage = finish;
		}

		//���캯������ vector<T> v6(b,e)
		vector(const iterator& b, const iterator& e) {
			start = allocate_and_copy(b, e, size_type(e - b + 1));
			finish = start + (e - b + 1);
			end_of_storage = finish;
		}

		~vector() {
			vector_allocator::destroy(start, finish);
			vector_allocator::deallocate(start, end_of_storage - start);
		}

		//��Ԫ�ز��뵽ĩβ
		void push_back(const T& value) {
			if (finish != end_of_storage) {
				vector_allocator::construct(finish, value);
				++finish;
			}else {
				//��������ռ�
				const size_type old_size = size();
				const size_type new_size = (old_size == 0) ? 1 : 2 * old_size;
				iterator new_start = vector_allocator::allocate(new_size,0);
				iterator new_finish = new_start;
				//�ڴ�ķ���Ҫ��ԭ���ԣ�Ҫôȫ���ɹ���Ҫôȫ��ʧ��
				try {
					//1.��ԭ���ݿ�������vector��
					//2.Ϊ�µ�Ԫ�����ó�ֵ
					//3.����
					for (iterator it = begin(); it < end(); ++it) {
						vector_allocator::construct(new_finish++, *it);
					}
					vector_allocator::construct(new_finish, value);
					++new_finish;
				}
				catch (...) {
					//���ʧ����
					vector_allocator::destroy(new_start, new_finish);//ɾ�����뵽���ڴ�
					new_start = new_finish = nullptr;
					throw;

				}

				//�������ͷ�ԭvector
				vector_allocator::destroy(begin(), end());
				//ɾ���ڴ�
				free(start);
				//������������ָ���µ�vector
				start = new_start;
				finish = new_finish;
				end_of_storage = new_start + new_size;
			}
		}
		
		//��β��Ԫ��ɾ������������С
		void pop_back() {
			--finish;
			vector_allocator::destroy(finish);
		}

		//���[first,last)֮�����е�Ԫ��
		iterator erase(iterator first, iterator last) {
			//β������������
			difference_type left_of_trail = end() - last;
			//ɾȥ�Ķ�����Ŀ
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
				//����ռ䣬������ֵ���ռ���
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

			//��first��last�������м��Ԫ�ؿ�����start��ʼ���ڴ���
			iterator copy(iterator first, iterator last, iterator start) {
				while (fisrt < last) {
					*start++ = sirst++;
				}
				return start;
			}

			iterator allocate_and_fill(size_type n, const T& value) {
				//����ռ䲢����ʼֵ
				iterator ret = vector_allocator::allocate(n);
				//�����ڴ�ɹ����ڵõ����ڴ��ϴ�������
				if (ret) {
					start = ret;
					end_of_storage = start + n;
					finish = end_of_storage;
					while (n--) {
						//���ڴ���һ��һ���ع������
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



