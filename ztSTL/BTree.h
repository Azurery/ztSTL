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
		KeyType* key_value;	//�ؼ��ֵ�����
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
		key_value = new KeyType[2 * min_degree - 1];
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
		void split_child(btree_node<KeyType>* node_parent, int child_index);
		void insert(KeyType value);
		void insert_not_full(btree_node<KeyType>* node, KeyType value);
		btree_node<KeyType>* find(btree_node<KeyType>* node, KeyType value);	//�����Ƿ�����ͬԪ���ڽ����
		void delete_balance(btree_node<KeyType>* node, KeyType value);	//�õݹ�ɾ�����޸�
	};

	//����B���еĽ��
	template<typename KeyType>
	void btree<KeyType>::split_child(btree_node<KeyType>* node_parent, int child_index){
		btree_node<KeyType>* pre_child = node_parent->child[child_index];	//pre_childΪ����ǰnode_parent���ӽ������
		//�ȴ���һ�����node_right,���ָ��Ժ�����ӽ��
		btree_node<KeyType>* node_right = new btree_node<KeyType>();
		node_right->is_leaf = pre_child->is_leaf;
		node_right->cur_node_key_nums = MIN_DEGREE;
		//node_right�����ؼ���
		for (int i = 0; i < MINI_KEY_NUMS; ++i) {
			node_right->key_value[child_index] = pre_child->key_value[i + MIN_DEGREE];
		}
		//�жϷ��ѵĽ���Ƿ�ΪҶ�ӽڵ㡣������ǣ��ͽ����Ӹ��ƹ�ȥ
		if (!node_right->is_leaf) {
			for (int i = 0; i < MIN_DEGREE; ++i) {
				node_right->child[i] = pre_child->child[i + MIN_DEGREE];
			}
		}
		//�������ӽ��Ĺؼ�����
		pre_child->cur_node_key_nums = MINI_KEY_NUMS;
		//�������ؼ��ֺ���ָ�����
		for (int i = node_parent->cur_node_key_nums + 1; i > child_index + 1; --i) {
			node_parent->child[i + 1] = node_parent->child[i];
			node_parent->key_value[i] = node_parent->key_value[i - 1];
		}
		node_parent->child[child_index + 1] = node_right;
		//��֮ǰ�ӽ��pre_child���м�ؼ����ᵽ�����node_parent֮�У����ָ�pre_child��node_right
		for (int j = node_parent->cur_node_key_nums; j > child_index; --j) {
			node_parent->key_value[j + 1] = pre_child[j];
		}
		node_parent->key_value[child_index] = pre_child[child_index];
		node_parent->cur_node_key_nums++;	//���¸����ؼ��ָ���
	}

	//��B���в����Ը��ؼ���
	template<typename KeyType>
	void btree<KeyType>::insert(KeyType value){
		if (root == nullptr) 
			root = new btree_node<KeyType>();
		//������ڵ�rootΪ��ʱ
		if (root->cur_node_key_nums == MAX_KEY_NUMS) {
			//����һ���½��new_node���ý�㽫��Ϊ�µĸ�
			btree_node<KeyType>* new_node = new btree_node<KeyType>();
			new_node->child[0] = root;
			new_node->is_leaf = false;	//��ʱnew_node�Ѿ�������Ҷ�ӽ��
			new_node->cur_node_key_nums = 0;
			split_child(new_node, 0);	//��������
		}
		else {
			insert_not_full(root, value);
		}
	}

	//��δ���Ľ�������ӹؼ���
	//����nodeΪ��Ҫ����Ľ��λ�ã�valueΪ��Ҫ�����ֵ
	template<typename KeyType>
	void btree<KeyType>::insert_not_full(btree_node<KeyType>* node, KeyType value){
		//��ò�����Ĺؼ��ָ���
		int node_key_nums = node->cur_node_key_nums;
		if (node->is_leaf) {	//�����ǰ���ΪҶ�ӽ��
			while (node_key_nums > 0 && value < node->key_value[node_key_nums - 1]) {
				//���ؼ��������ƶ�
				node->key_value[node_key_nums] = node->key_value[node_key_nums - 1];
				--node_key_nums;	//��ǰ�ƶ�
			}
			node->key_value[node_key_nums] = value;
			node->cur_node_key_nums++;	//��ǰ���Ĺؼ��ָ�����1
		}
		else {	
			//nodeΪ�ڲ����,�������node���Ǹ��ڲ��ӽ��ݹ��½�
			//�ڱ�valueС�ʹ���м��Ǹ��ӽ�����Һ��ʵ�λ��
			//����������е�ֵ��С�����ڵ�һ���ӽ����Ѱ��
			while (node_key_nums > 0 && value < node->key_value[node_key_nums - 1]) {
				--node_key_nums;
			}
			++node_key_nums;
			//��node_child���洢��������ӽ��
			btree_node<KeyType>* node_child=node->child[node_key_nums];
			if (node_child->cur_node_key_nums == MAX_KEY_NUMS) {
				split_child(node, node_key_nums);
				//�Ƚϲ���ֵ���ӽ��Ĵ�С
				if (value > node->child[node_key_nums + 1]) {
					++node_key_nums;
				}
			}
			insert_not_full(node_child, value);
		}
	}

	//�����Ƿ�����ͬԪ���ڽ����
	template<typename KeyType>
	btree_node<KeyType>* btree<KeyType>::find(btree_node<KeyType>* node, KeyType value){
		int i;
		if (node == nullptr)
			return NULL;
		else {		//��ǰ��㲻Ϊ��ʱ
			//�ڱ�value���С���м�����Ѱ����ȵĽ��
			for (i = 0; i < node->cur_node_key_nums; ++i) {
				if (value <= node->key_value[i])
					break;
			}
			//У�鵱ǰ�Ĺؼ����Ƿ���ڲ��ҵĹؼ���
			if (i < node->cur_node_key_nums&&value == node->key_value[i]) {
				return node;
			}
			else {
				if (node->is_leaf) //���û����value��ȵĹؼ��ֲ��ҵ�ǰ�����Ҷ�ӽ��Ļ�������B����û��һ���Ĺؼ���
					return NULL;
				else {  //�������Ҷ�ӽ�㣬����������ӽ����Ѱ��
					return btree_node(node->child[i], value);
				}
			}
		}
	}

	template<typename KeyType>
	void btree<KeyType>::delete_balance(btree_node<KeyType>* node, KeyType value){
		int i;
		//�ڵ�ǰ���node�в��Һ��ʵ�����ʹ��value�����������
		for (i = 0; i<node->cur_node_key_nums&&value>node->key_value[i]; ++i) {

		}
		//�����ǰi�Ĺؼ��ֵ���value
		if (i < node->cur_node_key_nums&&value == node->key_value[i]) {
			if (node->is_leaf) {	//�����ǰ�ӵ���Ҷ�ӽ��Ļ�����ֱ��ɾ��
				--node->cur_node_key_nums;
				//��i�����Ԫ�ض�����һλ
				for (; i < node->cur_node_key_nums; ++i) {
					node->key_value[i] = node->key_value[i + 1];
				}
				return;
			}
			else {
				//���
			}
		}
	}


}
#endif
