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
		KeyType* key_value;	//关键字的数组
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
		key_value = new KeyType[2 * min_degree - 1];
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
		void split_child(btree_node<KeyType>* node_parent, int child_index);
		void insert(KeyType value);
		void insert_not_full(btree_node<KeyType>* node, KeyType value);
		btree_node<KeyType>* find(btree_node<KeyType>* node, KeyType value);	//查找是否有相同元素在结点中
		void delete_balance(btree_node<KeyType>* node, KeyType value);	//用递归删除并修复
	};

	//分裂B树中的结点
	template<typename KeyType>
	void btree<KeyType>::split_child(btree_node<KeyType>* node_parent, int child_index){
		btree_node<KeyType>* pre_child = node_parent->child[child_index];	//pre_child为分列前node_parent的子结点数组
		//先创建一个结点node_right,即分割以后的右子结点
		btree_node<KeyType>* node_right = new btree_node<KeyType>();
		node_right->is_leaf = pre_child->is_leaf;
		node_right->cur_node_key_nums = MIN_DEGREE;
		//node_right拷贝关键字
		for (int i = 0; i < MINI_KEY_NUMS; ++i) {
			node_right->key_value[child_index] = pre_child->key_value[i + MIN_DEGREE];
		}
		//判断分裂的结点是否为叶子节点。如果不是，就将孩子复制过去
		if (!node_right->is_leaf) {
			for (int i = 0; i < MIN_DEGREE; ++i) {
				node_right->child[i] = pre_child->child[i + MIN_DEGREE];
			}
		}
		//更新左子结点的关键字数
		pre_child->cur_node_key_nums = MINI_KEY_NUMS;
		//将父结点关键字和子指针后移
		for (int i = node_parent->cur_node_key_nums + 1; i > child_index + 1; --i) {
			node_parent->child[i + 1] = node_parent->child[i];
			node_parent->key_value[i] = node_parent->key_value[i - 1];
		}
		node_parent->child[child_index + 1] = node_right;
		//将之前子结点pre_child的中间关键字提到父结点node_parent之中，来分隔pre_child和node_right
		for (int j = node_parent->cur_node_key_nums; j > child_index; --j) {
			node_parent->key_value[j + 1] = pre_child[j];
		}
		node_parent->key_value[child_index] = pre_child[child_index];
		node_parent->cur_node_key_nums++;	//更新父结点关键字个数
	}

	//在B树中插入以各关键字
	template<typename KeyType>
	void btree<KeyType>::insert(KeyType value){
		if (root == nullptr) 
			root = new btree_node<KeyType>();
		//如果根节点root为满时
		if (root->cur_node_key_nums == MAX_KEY_NUMS) {
			//创建一个新结点new_node，该结点将成为新的根
			btree_node<KeyType>* new_node = new btree_node<KeyType>();
			new_node->child[0] = root;
			new_node->is_leaf = false;	//此时new_node已经不再是叶子结点
			new_node->cur_node_key_nums = 0;
			split_child(new_node, 0);	//将结点分裂
		}
		else {
			insert_not_full(root, value);
		}
	}

	//向未满的结点中增加关键字
	//参数node为所要插入的结点位置，value为将要插入的值
	template<typename KeyType>
	void btree<KeyType>::insert_not_full(btree_node<KeyType>* node, KeyType value){
		//获得插入结点的关键字个数
		int node_key_nums = node->cur_node_key_nums;
		if (node->is_leaf) {	//如果当前结点为叶子结点
			while (node_key_nums > 0 && value < node->key_value[node_key_nums - 1]) {
				//将关键字往后移动
				node->key_value[node_key_nums] = node->key_value[node_key_nums - 1];
				--node_key_nums;	//向前移动
			}
			node->key_value[node_key_nums] = value;
			node->cur_node_key_nums++;	//当前结点的关键字个数加1
		}
		else {	
			//node为内部结点,则决定向node的那个内部子结点递归下降
			//在比value小和大的中间那个子结点中找合适的位置
			//如果它比所有的值都小，则在第一个子结点中寻找
			while (node_key_nums > 0 && value < node->key_value[node_key_nums - 1]) {
				--node_key_nums;
			}
			++node_key_nums;
			//用node_child来存储插入结点的子结点
			btree_node<KeyType>* node_child=node->child[node_key_nums];
			if (node_child->cur_node_key_nums == MAX_KEY_NUMS) {
				split_child(node, node_key_nums);
				//比较插入值和子结点的大小
				if (value > node->child[node_key_nums + 1]) {
					++node_key_nums;
				}
			}
			insert_not_full(node_child, value);
		}
	}

	//查找是否有相同元素在结点中
	template<typename KeyType>
	btree_node<KeyType>* btree<KeyType>::find(btree_node<KeyType>* node, KeyType value){
		int i;
		if (node == nullptr)
			return NULL;
		else {		//当前结点不为空时
			//在比value大和小的中间结点中寻找相等的结点
			for (i = 0; i < node->cur_node_key_nums; ++i) {
				if (value <= node->key_value[i])
					break;
			}
			//校验当前的关键字是否等于查找的关键字
			if (i < node->cur_node_key_nums&&value == node->key_value[i]) {
				return node;
			}
			else {
				if (node->is_leaf) //如果没有与value相等的关键字并且当前结点是叶子结点的话，则在B树中没有一样的关键字
					return NULL;
				else {  //如果不是叶子结点，则在下面的子结点中寻找
					return btree_node(node->child[i], value);
				}
			}
		}
	}

	template<typename KeyType>
	void btree<KeyType>::delete_balance(btree_node<KeyType>* node, KeyType value){
		int i;
		//在当前结点node中查找合适的坐标使得value在这个区间内
		for (i = 0; i<node->cur_node_key_nums&&value>node->key_value[i]; ++i) {

		}
		//如果当前i的关键字等于value
		if (i < node->cur_node_key_nums&&value == node->key_value[i]) {
			if (node->is_leaf) {	//如果当前接电视叶子结点的话，就直接删除
				--node->cur_node_key_nums;
				//把i后面的元素都后移一位
				for (; i < node->cur_node_key_nums; ++i) {
					node->key_value[i] = node->key_value[i + 1];
				}
				return;
			}
			else {
				//如果
			}
		}
	}


}
#endif
