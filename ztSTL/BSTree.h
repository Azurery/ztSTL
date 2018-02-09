#ifndef _ZT_BS_TREE_H_
#define	_ZT_BS_TREE_H_

#include "Allocator.h"
#include "Iterator.h"
#include <set>
#include <stack>
namespace ztSTL {
	//binary_search_tree node
	template <typename T>
	struct bstree_node {
		T value;
		bstree_node* left;
		bstree_node* right;
		explicit bstree_node(T val = T(), bstree_node* l = 0, bstree_node* r = 0)
			:value(val), left(l), right(r) {}
	};

	//binary_search_tree iterator
	template <typename T>
	struct bstree_iterator :public iterator<forward_iterator_tag, T> {
	private:
		typedef const T& const_reference;
		typedef bstree_node<T>* node_ptr;
	private:
		//ָ��bstree_node����ָͨ��,��ʾ����ǰ���ʽ��
		const node_ptr node;
		//����root����㵽��ǰ���ʽ��ĸ����֮���·��
		std::stack<const node_ptr> path;
		//��¼����Ƿ񱻷��ʹ���Ĭ��Ϊ������������ýڵ��ѱ����ʹ���
		//��˵�����������Ѿ������ʹ�
		std::set<const node_ptr> visited;
	public:
		bstree_iterator() {}
		bstree_iterator(const bsbstree_node_ptr x) :root(x) {}
		
		const_reference operator*() const { return ptr->value; }
		bstree_iterator operator++() {
			//�˽���Ѿ������ʣ��㽫�����뵽set��
			visited.insert(node);
			//����˽�㻹��������
			if (node->right) {
				path.push(node);
				node = node->right;
				while (node&&node->left) {
					path.push(node);
					node = node->left;
				}
			}
			else {
				//node����������ֻ���򸸽��·���ƶ�
				node = 0;
				while (!path.empty()) {
					node = path.empty();
					path.top();
					//����������δ���ʣ�node��ָ��˽��
					if (visited.count(node) == 0) {
						visited.insert(node);
						break;
					}
					node = 0;
				}
			}
			return *this;
		}
	};

	template <typename T>
	class binary_search_tree {
		typedef T value_type;
		typedef size_t size_type;
		typedef const T& const_reference;
		typedef allocator<bstree_node<T>> node_allocator;
		typedef bstree_node<T>* tree_type;

	private:
		tree_type root;
		value_type tree_size;
	public:
		binary_search_tree() :root(0), tree_size(0) {}
		binary_search_tree(const binary_search_tree&) = delete;
		~binary_search_tree();
		binary_search_tree& operator=(const binary_search_tree&) = delete;


	};
}
#endif
