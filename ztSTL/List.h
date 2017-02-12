#ifndef _ZT_LIST_H_
#define _ZT_LIST_H_
#include "Iterator.h"
#include "Allocator.h"

namespace ztSTL {
	//双链表结点：list_node
	template <typename T>
	struct list_node {
		T value;
		list_node* prev;
		list_node* next;
		list_node(const T& val, list_node* p, list_node* n) :
			value(val), prev(p), next(n) {}
		/*bool operator ==(const list_node& n) {
			return value == n.value && prev == n.prev && next == n.next;
		}*/
	};

	//双链表迭代器：list_iterator
	template <typename T>
	struct list_iterator :public iterator<bidirectional_iterator_tag, T> {
		typedef list_node<T>* lnode_ptr;
	private:
		//指向list结点的普通指针
		lnode_ptr node;
	public:
		//构造函数
		list_iterator(){}
		list_iterator(lnode_ptr x) :node(x) {}
		list_iterator(const iterator& x) :node(x.lnode_ptr) {}

		pointer operator->() const { return &(operator*()); }
		reference operator*() const { return node->value; }
		bool operator==(const list_iterator<T>& li) const {
			return node == li.node;
		}
		bool operator!=(const list_iterator<T>& li) const {
			return !(node == li.node);
		}
		//对迭代器递增1，即访问下一个结点
		//前置版本
		list_iterator& operator++() {
			node = node->next;
			return *this;
		}
		//后置版本
		list_iterator operator++(int) {
			list_iterator ret = *this;
			++*this;
			return ret;
		}

		//对迭代器递减1，即访问前一个结点
		list_iterator& operator--() {
			node = node->prev;
			return *this;
		}
		list_iterator operator--(int) {
			list_iterator ret = *this;
			--*this;
			return ret;
		}
	};

	//双链表数据结构：list
	template<typename T>
	class list {
		template<typename T>
		friend struct list_iterator;
	private:
		typedef size_t size_type;
		typedef T value_type;
		typedef list_iterator<T> iterator;
		typedef list_iterator<const T> const_iterator;
		typedef T& reference;
		typedef list_node<T>* lnode_type;
		typedef allocator<list_node<T>> node_allocator;
	private:
		iterator head;
		iterator tail;
	public:
		list() {
			head.node = create_node();
			tail.node = head.node;
		};
		list(const list& l) {

		}
		iterator begin() { return head; }
		iterator end() { return tail; }
		bool empty() const { return head == tail; }
		size_type size() {
			size_type count = 0;
			for (auto beg = begin(); beg != end(); ++beg) {
				++count;
			}
			return count;
		}
		reference front() { return *begin(); }
		reference back() { return *(--end()); }
		//在迭代器pos所指的位置插入一个结点，值为value
		iterator insert(iterator pos, const value_type& value) {
			lnode_type cur = create_node();
			lnode_type pnode = static_cast<lnode_type>(pos.node);
			cur->value = value;
			cur->prev = pnode->prev;
			pnode->prev->next = cur;
			cur->next = pnode;
			pnode->prev = cur;
			return cur;
		}
		//在头结点插入值
		void push_front(const value_type& value) {
			auto new_head = create_node(value);
			(head.node)->prev = new_head;
			new_head->next = head.node;
			head.node = new_head;
		}
		//在尾结点后插入值
		void push_back(const value_type& value) {
			//insert(end(), value);
			auto new_tail = create_node();
			(tail.node)->value = value;
			(tail.node)->next = new_tail;
			new_tail->prev = tail.node;
			tail.node = new_tail;

		}
		//删除所有元素
		void clear() {
			while (!empty()) {
				pop_back();
			}
		}
		//移除pos位置处的迭代器
		iterator erase(iterator pos) {
			if (pos == head) {
				pop_front();
				return head;
			}
			else {
				auto prev = pos.node->prev;
				prev->next = pos.node->next;
				pos.node->next->prev = prev;
				destroy_node(pos.node);
				return static_cast<iterator>(pos.node->next);
			}

		}
		//移除b与e迭代器之间的数据
		iterator erase(iterator first, iterator last) {
			iterator ret;
			for (auto beg = first; beg != last; ++beg) {
				ret = erase(beg);
			}
			return ret;
		}
		//删除头结点
		void pop_front() {
			auto new_head = head.node->next;
			destroy_node(head.node);
			head.node = new_head;
		}
		//删除尾节点
		void pop_back() {
			auto new_tail = tail.node->prev;
			new_tail->next = nullptr;
			destroy_node(tail.node);
			tail.node = new_tail;
		}
		//合并两个sorted list
		void merge(list& l) {

		}
		//翻转双链表
		void reverse(list& l) {
			if (empty() || head.node->next == nullptr)	return;

		}

	private:
		/*lnode_type create_node() {
			return node_allocator::allocate();
		}*/
		static lnode_type create_node(const value_type& value = T()) {
			//产生一个结点，将元素传入其中
			lnode_type ret = node_allocator::allocate();
			node_allocator::construct(ret, list_node<T>(value, nullptr, nullptr));
			return ret;
		}
		static void destroy_node(lnode_type p) {
			node_allocator::destroy(p);
		}

	};
}
#endif
