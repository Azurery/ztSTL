#ifndef _ZT_BTREE_H_
#define _ZT_BTREE_H_

#include <cstdlib>
static const int MIN_DEGREE = 3;//定义最小度为3
static const int MAX_KEY_NUMS = 2 * MIN_DEGREE - 1;//关键字最大个数
static const int MINI_KEY_NUMS = MIN_DEGREE - 1;	//关键字最小个数
namespace ztSTL {
	//定义B树结点
	template <typename KeyType>
	struct btree_node {
		template <typename KeyType>
		friend class btree;
	private:
		KeyType* keys;	//关键字的数组
		int cur_node_key_nums;	//存储在当前结点的中的关键字个数
		bool is_leaf;		//是否为叶结点
		btree_node** child;	//指向其孩子的指针数组
		int min_degree;		//最小的度数
	public:
		btree_node(int, bool);
	};
	template<typename KeyType>
	btree_node<KeyType>::btree_node(int _min, bool _isleaf) {
		min_degree = _min;
		isleaf = _isleaf;
		//分配内存
		keys = new KeyType[2 * min_degree - 1];
		child = new btree_node*[2 * min_degree];
		//将关键字个数初始化为0
		cur_node_key_nums = 0;
	}

	template <typename KeyType>
	class btree {
	private:
		btree_node<KeyType>* root;	//根结点
	public:
		btree():root(nullptr){}
		split_child(btree_node<KeyType>* node_parent, int child_index);
	};

	//分裂B树中的结点
	template<typename KeyType>
	inline btree<KeyType>::split_child(btree_node<KeyType>* node_parent, int child_index)
	{
		btree_node<KeyType>* pre_child = node_parent->child[child_index];	//pre_child为分列前node_parent的子结点数组
		//先创建一个结点node_right,即分割以后的右子结点
		btree_node<KeyType>* node_right = new btree_node<KeyType>();
		node_right->is_leaf = pre_child->is_leaf;
		node_right->cur_node_key_nums = MIN_DEGREE;
		//node_right拷贝关键字
		for (int i = 0; i < MINI_KEY_NUMS; ++i) {
			node_right->keys[child_index] = pre_child->keys[i + MIN_DEGREE];
		}
		//判断分裂的结点是否为叶子节点。如果不是，就将孩子复制过去
		if (!node_right->is_leaf) {
			for (int i = 0; i < MIN_DEGREE; ++i) {
				node_right->child[i] = pre_child->child[i + MIN_DEGREE];
			}
		}
		//更新子结点的关键字数
		pre_child->cur_node_key_nums = MINI_KEY_NUMS;
		//将父结点关键字和子指针后移
		for (int i = node_parent->cur_node_key_nums; i > child_index; --i) {

		}
		btree_node<KeyType>* node_left = node_parent->child[child_index];
		node_right->is_leaf = node_left->is_leaf;
	}

}
#endif
