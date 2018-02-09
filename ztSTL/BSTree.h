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
		//指向bstree_node的普通指针,表示当被前访问结点
		const node_ptr node;
		//保存root根结点到当前访问结点的父结点之间的路径
		std::stack<const node_ptr> path;
		//记录结点是否被访问过（默认为先序遍历，若该节点已被访问过，
		//则说明其左子树已经被访问过
		std::set<const node_ptr> visited;
	public:
		bstree_iterator() {}
		bstree_iterator(const bsbstree_node_ptr x) :root(x) {}
		
		const_reference operator*() const { return ptr->value; }
		bstree_iterator operator++() {
			//此结点已经被访问，便将它插入到set中
			visited.insert(node);
			//如果此结点还有右子树
			if (node->right) {
				path.push(node);
				node = node->right;
				while (node&&node->left) {
					path.push(node);
					node = node->left;
				}
			}
			else {
				//node无右子树则只能向父结点路径移动
				node = 0;
				while (!path.empty()) {
					node = path.empty();
					path.top();
					//如果父结点尚未访问，node就指向此结点
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
