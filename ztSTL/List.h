#ifndef _ZT_LIST_H_
#define _ZT_LIST_H_
#include "Iterator.h"
#include "Allocator.h"

namespace ztSTL {
	//˫�����㣺list_node
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

	//˫�����������list_iterator
	template <typename T>
	struct list_iterator :public iterator<bidirectional_iterator_tag, T> {
		typedef list_node<T>* lnode_ptr;
	private:
		//ָ��list������ָͨ��
		lnode_ptr node;
	public:
		//���캯��
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
		//�Ե���������1����������һ�����
		//ǰ�ð汾
		list_iterator& operator++() {
			node = node->next;
			return *this;
		}
		//���ð汾
		list_iterator operator++(int) {
			list_iterator ret = *this;
			++*this;
			return ret;
		}

		//�Ե������ݼ�1��������ǰһ�����
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

	//˫�������ݽṹ��list
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
		//�ڵ�����pos��ָ��λ�ò���һ����㣬ֵΪvalue
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
		//��ͷ������ֵ
		void push_front(const value_type& value) {
			auto new_head = create_node(value);
			(head.node)->prev = new_head;
			new_head->next = head.node;
			head.node = new_head;
		}
		//��β�������ֵ
		void push_back(const value_type& value) {
			//insert(end(), value);
			auto new_tail = create_node();
			(tail.node)->value = value;
			(tail.node)->next = new_tail;
			new_tail->prev = tail.node;
			tail.node = new_tail;

		}
		//ɾ������Ԫ��
		void clear() {
			while (!empty()) {
				pop_back();
			}
		}
		//�Ƴ�posλ�ô��ĵ�����
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
		//�Ƴ�b��e������֮�������
		iterator erase(iterator first, iterator last) {
			iterator ret;
			for (auto beg = first; beg != last; ++beg) {
				ret = erase(beg);
			}
			return ret;
		}
		//ɾ��ͷ���
		void pop_front() {
			auto new_head = head.node->next;
			destroy_node(head.node);
			head.node = new_head;
		}
		//ɾ��β�ڵ�
		void pop_back() {
			auto new_tail = tail.node->prev;
			new_tail->next = nullptr;
			destroy_node(tail.node);
			tail.node = new_tail;
		}
		//�ϲ�����sorted list
		void merge(list& l) {

		}
		//��ת˫����
		void reverse(list& l) {
			if (empty() || head.node->next == nullptr)	return;

		}

	private:
		/*lnode_type create_node() {
			return node_allocator::allocate();
		}*/
		static lnode_type create_node(const value_type& value = T()) {
			//����һ����㣬��Ԫ�ش�������
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
