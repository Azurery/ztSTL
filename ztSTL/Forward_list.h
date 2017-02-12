#ifndef _ZT_FORWARD_LIST_H_
#define _ZT_FORWARD_LIST_H_

#include "Allocator.h"
#include "Iterator.h"

namespace ztSTL {
	//单链表结点:forward_list_node
	template <typename T>
	struct forward_list_node {
		T value;
		forward_list_node* next;
		forward_list_node(const T& val, forward_list_node* fln) :
			value(val), next(fln) {}
	};

	//单链表的迭代器：forward_list_iterator
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
		//因为这是一个forward_list_node单链表，故不能实现operator--
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
		flnode_type* head;	//注意：head不是指针，而是实物
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
		//取头部元素
		reference front() { return *begin(); }
		//从头部插入元素（新元素成为forward_list的第一个元素）
		void push_front(const value_type& value){
			auto new_head=create_node(value);
			new_head->next = head;
			head= new_head;
		}
		//删除头部元素
		void pop_front() {
			flnode_type* new_head = head->next;
			head = new_head;
			destroy_node(new_head);
		}
		//删除位置pos后的一个元素
		iterator erase_after(iterator pos) {

		}
		//翻转单链表
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
		//合并两个sorted forward_list
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