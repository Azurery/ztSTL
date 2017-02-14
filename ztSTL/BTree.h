#ifndef _ZT_BTREE_H_
#define _ZT_BTREE_H_

#include <cstdlib>
static const int MIN_DEGREE = 3;//������С��Ϊ3
static const int MAX_KEY_NUMS = 2 * MIN_DEGREE - 1;//�ؼ���������
static const int MINI_KEY_NUMS = MIN_DEGREE - 1;	//�ؼ�����С����
namespace ztSTL {
	//����B�����
	template <typename KeyType>
	struct btree_node {
		template <typename KeyType>
		friend class btree;
	private:
		KeyType* keys;	//�ؼ��ֵ�����
		int cur_node_key_nums;	//�洢�ڵ�ǰ�����еĹؼ��ָ���
		bool is_leaf;		//�Ƿ�ΪҶ���
		btree_node** child;	//ָ���亢�ӵ�ָ������
		int min_degree;		//��С�Ķ���
	public:
		btree_node(int, bool);
	};
	template<typename KeyType>
	btree_node<KeyType>::btree_node(int _min, bool _isleaf) {
		min_degree = _min;
		isleaf = _isleaf;
		//�����ڴ�
		keys = new KeyType[2 * min_degree - 1];
		child = new btree_node*[2 * min_degree];
		//���ؼ��ָ�����ʼ��Ϊ0
		cur_node_key_nums = 0;
	}

	template <typename KeyType>
	class btree {
	private:
		btree_node<KeyType>* root;	//�����
	public:
		btree():root(nullptr){}
		split_child(btree_node<KeyType>* node_parent, int child_index);
	};

	//����B���еĽ��
	template<typename KeyType>
	inline btree<KeyType>::split_child(btree_node<KeyType>* node_parent, int child_index)
	{
		btree_node<KeyType>* pre_child = node_parent->child[child_index];	//pre_childΪ����ǰnode_parent���ӽ������
		//�ȴ���һ�����node_right,���ָ��Ժ�����ӽ��
		btree_node<KeyType>* node_right = new btree_node<KeyType>();
		node_right->is_leaf = pre_child->is_leaf;
		node_right->cur_node_key_nums = MIN_DEGREE;
		//node_right�����ؼ���
		for (int i = 0; i < MINI_KEY_NUMS; ++i) {
			node_right->keys[child_index] = pre_child->keys[i + MIN_DEGREE];
		}
		//�жϷ��ѵĽ���Ƿ�ΪҶ�ӽڵ㡣������ǣ��ͽ����Ӹ��ƹ�ȥ
		if (!node_right->is_leaf) {
			for (int i = 0; i < MIN_DEGREE; ++i) {
				node_right->child[i] = pre_child->child[i + MIN_DEGREE];
			}
		}
		//�����ӽ��Ĺؼ�����
		pre_child->cur_node_key_nums = MINI_KEY_NUMS;
		//�������ؼ��ֺ���ָ�����
		for (int i = node_parent->cur_node_key_nums; i > child_index; --i) {

		}
		btree_node<KeyType>* node_left = node_parent->child[child_index];
		node_right->is_leaf = node_left->is_leaf;
	}

}
#endif
