#ifndef _ZT_BTREE_H_
#define _ZT_BTREE_H_

#include "Allocator.h"

namespace ztSTL {
	//定义B树结点
	template <typename KeyType>
	struct btree_node {
		friend class btree<KeyType>;
	private:
		KeyType* keys;	//关键字的数组
		int cur_node_key_nums;	//存储在当前结点的中的关键字个数
		bool is_leaf;		//是否为叶结点
		btree_node** child;	//指向其孩子的指针数组
		int min_degree;		//最小的度数
	};
	//template<typename KeyType>
	//btree_node<KeyType>::btree_node(int _min, bool _isleaf) {
	//	min_degree = _min;
	//	isleaf = _isleaf;
	//	//分配内存
	//	keys = node_allocater::allocate(2 * min_degree - 1);
	//	child = new btree_node*[2 * min_degree];
	//	//将关键字个数初始化为0
	//	cur_node_key_nums = 0;
	//}

	////遍历当前结点和当前结点下的子树
	//template<typename KeyType>
	//inline void btree_node<KeyType>::traverse(){
	//	int i;
	//	//cur_node_key_nums个关键字和cur_node_key_nums+1个孩子
	//	for (i = 0; i < cur_node_key_nums; ++i) {

	//	}
	//}

	template <typename KeyType>
	class btree {
	private:
		typedef allocator<KeyType> node_allocater;
	public:
		btree_node* create_new_node();
		

		~btree_node();

		void traverse();	//遍历B树
		btree_node* search(int val);	//在B树中查找val
	};

}
#endif
