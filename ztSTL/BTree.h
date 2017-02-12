#ifndef _ZT_BTREE_H_
#define _ZT_BTREE_H_

#include "Allocator.h"

namespace ztSTL {
	//����B�����
	template <typename KeyType>
	struct btree_node {
		friend class btree<KeyType>;
	private:
		KeyType* keys;	//�ؼ��ֵ�����
		int cur_node_key_nums;	//�洢�ڵ�ǰ�����еĹؼ��ָ���
		bool is_leaf;		//�Ƿ�ΪҶ���
		btree_node** child;	//ָ���亢�ӵ�ָ������
		int min_degree;		//��С�Ķ���
	};
	//template<typename KeyType>
	//btree_node<KeyType>::btree_node(int _min, bool _isleaf) {
	//	min_degree = _min;
	//	isleaf = _isleaf;
	//	//�����ڴ�
	//	keys = node_allocater::allocate(2 * min_degree - 1);
	//	child = new btree_node*[2 * min_degree];
	//	//���ؼ��ָ�����ʼ��Ϊ0
	//	cur_node_key_nums = 0;
	//}

	////������ǰ���͵�ǰ����µ�����
	//template<typename KeyType>
	//inline void btree_node<KeyType>::traverse(){
	//	int i;
	//	//cur_node_key_nums���ؼ��ֺ�cur_node_key_nums+1������
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

		void traverse();	//����B��
		btree_node* search(int val);	//��B���в���val
	};

}
#endif
