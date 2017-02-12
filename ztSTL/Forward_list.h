#ifndef _ZT_FORWARD_LIST_H_
#define _ZT_FORWARD_LIST_H_

#include "Allocator.h"
#include "Iterator.h"

namespace ztSTL {
	//��������:forward_list_node
	template <typename T>
	struct forward_list_node {
		T value;
		forward_list_node* next;
		forward_list_node(const T& val, forward_list_node* fln) :
			value(val), next(fln) {}
	};

	//������ĵ�������forward_list_iterator
	template <typename T>
	struct forward_list_iterator :public iterator<forward_iterator_tag, T> {
	public:
		typedef forward_list_node<T>* node_ptr;
		node_ptr node;
	public:
		forward_list_iterator() :node(0) {};
		forward_list_iterator(node_ptr x) :node(x) {};

		reference operator*() const {return node->value;}
		pointer operator->() const {return &(operator*());}
		forward_list_iterator& operator++() {
			node = node->next;
			return *this;
		}
		forward_list_iterator operator++(int) {
			forward_list_iterator ret = *this;
			++*this;
			return ret;
		}
		//��Ϊ����һ��forward_list_node�������ʲ���ʵ��operator--
		bool operator==(const forward_list_iterator& fli) {
			return node == fli.node;
		}
		bool operator!=(const forward_list_iterator& fli) {
			return !(node == fli.node);
		}
	};

	template <typename T>
	class forward_list {
		template <typename T>
		friend struct forward_list_iterator;
	private:
		typedef size_t size_type;
		typedef T value_type;
		typedef T& reference;
		typedef forward_list_iterator<T> iterator;
		typedef allocator<forward_list_node<T>> node_allocator;
		typedef forward_list_node<T> flnode_type;
	private:
		flnode_type* head;	//ע�⣺head����ָ�룬����ʵ��
	public:
		forward_list() {}
		~forward_list() {}
		iterator begin() { return iterator(head); }
		iterator end() {
			flnode_type* cur = head;
			while (cur->next) {
				cur = cur->next;
			}
			return iterator(cur->next);
		}
		size_type size() {
			size_type count = 0;
			for (iterator beg = begin(); beg != end(); ++beg) {
				++count;
			}
			return count;
		}
		bool empty() const { return head == 0; }
		//ȡͷ��Ԫ��
		reference front() { return *begin(); }
		//��ͷ������Ԫ�أ���Ԫ�س�Ϊforward_list�ĵ�һ��Ԫ�أ�
		void push_front(const value_type& value){
			auto new_head=create_node(value);
			new_head->next = head;
			head= new_head;
		}
		//ɾ��ͷ��Ԫ��
		void pop_front() {
			flnode_type* new_head = head->next;
			head = new_head;
			destroy_node(new_head);
		}
		//ɾ��λ��pos���һ��Ԫ��
		iterator erase_after(iterator pos) {

		}
		//��ת������
		void reverse() {
			auto prev = head;
			auto cur= prev->next;
			prev->next = nullptr;
			while (cur) {
				auto _next=cur->next;
				cur->next=prev;
				prev = cur;
				cur = _next;
			}
			head = prev;	
		}
		//�ϲ�����sorted forward_list
		void merge(forward_list& fl) {
			
		}

	private:
		flnode_type* create_node(const value_type& value=T()) {
			flnode_type* ret = node_allocator::allocate();
			node_allocator::construct(ret,forward_list_node<T>(value,nullptr));
			return ret;
		}

		void destroy_node(flnode_type* p) {
			node_allocator::destroy(p);
		}










		
	};
}
#endif