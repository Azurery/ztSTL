#ifndef _ZT_GRAPH_H_
#define _ZT_GRAPH_H_

#include <iostream>

namespace ztSTL {
	const int MAX_NUM = 20;

	//ǰ������
	template <typename EdgeType, typename VertexType> class algraph;
	template <typename EdgeType, typename VertexType> class vertex_node;

	//���嶥���ڽӱ�Ľ��ṹ
	template <typename EdgeType>
	class edge_node {
		template<typename type1, typename type2> friend class vertex_node;
		template<typename type1, typename type2> friend class algraph;
	private:
		int vertex_index;		//�ñ��е��ڽӶ����ڶ�����е����
		EdgeType weight;//�ñߵ�Ȩ��
		edge_node *next;//ָ����һ���ߵ�ָ��
		edge_node() :next(nullptr) {}
		edge_node(int v, const EdgeType& w) :vertex_index(v), weight(w), next(nullptr) {}
	};

	//��������
	template <typename EdgeType, typename VertexType>
	class vertex_node {
		friend class algraph<EdgeType, VertexType>;
	private:
		VertexType value;		//���������
		edge_node<EdgeType> *first_edge_node;//�����ڽӱ���׽��ָ��
		vertex_node() :first_edge_node(nullptr) {}
	public:
		void clear_edge_list();			//ɾ���ö�����ڽӱ�
		bool append_edge(int, int = 0);//�ڸö�����ڽӱ��м���һ����
		bool remove_edge(int);	//�ڸö�����ڽӱ���ɾ��һ����
	};
	//���һ��������ڽ������ͷ��ڽӱ�ĸ����
	template <typename EdgeType, typename VertexType>
	void vertex_node<EdgeType, VertexType>::clear_edge_list() {
		edge_node<EdgeType>* cur = first_edge_node;
		edge_node<EdgeType>* _next;
		while (cur) {
			_next = cur->next;
			delete _next;
			cur = _next;
		}
		first_edge_node = nullptr;
	}
	//�ڸö�����ڽӱ��м���һ����
	//����_vertexΪ����ߵ��ڽӶ������,_weightΪ����ߵ�Ȩֵ
	template <typename EdgeType, typename VertexType>
	bool vertex_node<EdgeType, VertexType>::append_edge(int _vertex_index, int _weight) {
		edge_node<EdgeType>* cur = first_edge_node;
		edge_node<EdgeType>* temp = nullptr;
		//�ҵ��ڽ������ĩβ���
		while (cur != nullptr) {
			if (cur->vertex_index == _vertex_index)
				return false;
			temp = cur;
			cur = cur->next;
		}
		//���ڽӱ��������һ����
		edge_node<EdgeType>* new_node = new edge_node<EdgeType>(_vertex_index, _weight);
		//�������Ϊ�գ���ͷ�����Ϊ�½��
		if (temp == nullptr)
			first_edge_node = new_node;
		else
			temp->next = new_node;
		return true;
	}
	//�ڶ�����ڽӱ���ɾ��һ����
	template <typename EdgeType, typename VertexType>
	bool vertex_node<EdgeType, VertexType>::remove_edge(int _vertex_val) {
		edge_node* cur = first_edge_node;
		edge_node* temp = nullptr;
		//������ӱ�����ҵ������ߣ�����ɾ��
		while (cur) {
			if (cur->vertex_index == _vertex_val) {
				//���Ҫɾ������ͷ���
				if (cur == first_edge_node)
					first_edge_node = cur->next;
				else
					temp->next = cur->next;
				delete cur;
				return true;
			}
			temp = cur;
			cur = cur->next;
		}
		return false;
	}

	/*ͼ���ڽӱ���
	VertexType�Ƕ�����������ͣ����VertexType���Ǽ򵥵��������ͣ��ڶ���VertexTypeʱ��
	��������==����������ж��������������Ƿ����
	*/
	template<typename EdgeType, typename VertexType>
	class algraph {
	private:
	public:
		//ͼ����������
		enum algraph_type {
			DG,		//����ͼ
			DN,		//������
			UDG,	//����ͼ
			UDN		//������
		};
	private:
		vertex_node<EdgeType, VertexType> *vertex_table; //�����
		int vertex_num;	//�������
		int edge_num;	//����
		algraph_type graph;//ͼ������
	public:
		algraph() :vertex_table(nullptr), vertex_num(0), edge_num(0) {}
		algraph(VertexType *v, int num = MAX_NUM, algraph_type = UDG);
		~algraph();

		int locate_vertex(const VertexType&);  //���ݶ�������ݣ��ҵ������ڶ�����е����
		bool get_vertex_data(int, VertexType&);		//������ţ�ȡ�ö��������
		bool set_vertex_data(int, const VertexType&);//������ţ����ö��������	
		bool insert_vertex(const VertexType&);		//����һ������
		bool delete_vertex(const VertexType&);	//ɾ��һ������
		bool insert_edge(const EdgeType&, const VertexType&, const VertexType&);	//����һ����
		bool delete_edge(const VertexType&, const VertexType&);
		int get_first_vertex_index(int);
		bool get_edge(int, int, edge_node<EdgeType>*&);//���ݶ�����ţ�ȡ��������֮��ı�		
		bool get_vertex(int _vertex_index, VertexType& _vertex_val);
		bool empty() { return vertex_num == 0; }
		inline int get_vertex_nums() { return vertex_num; } //ȡ��ͼ�еĶ�����Ŀ
		inline int get_edge_nums() { return edge_num; }		//ȡ��ͼ�еı���

		bool get_vertex_value(VertexType& result, int v);
		bool get_weight(EdgeType& result, int v1, int v2);
		int getvertex_indexposition(int v);
		int get_next_vertex_index(int v1, int v2);
		void bfs(void(*visit)(const VertexType&));
		void dfs(void(*visit)(const VertexType&));
		void show();
	};
	//Ĭ��Ϊ����ͼUDG
	template<typename EdgeType, typename VertexType>
	algraph<EdgeType, VertexType>::algraph(VertexType *v, int num, algraph_type _graph) :
		vertex_num(0), edge_num(0), graph(_graph) {
		vertex_table = new vertex_node<EdgeType, VertexType>[num];
		for (int i = 0; i < num; ++i)
			insert_vertex(v[i]);
	}
	//��������
	template<typename EdgeType, typename VertexType>
	algraph<EdgeType, VertexType>::~algraph() {
		edge_node<EdgeType> *p;
		for (int i = 0; i < vertex_num; ++i) {
			//pָ���ڽӱ��ͷ���
			p = vertex_table[i].first_edge_node;
			while (p != nullptr) {
				vertex_table[i].first_edge_node = p->next;
				delete p;
				p = vertex_table[i].first_edge_node;
			}
		}
		delete[] vertex_table;
	}

	//���ݶ�������ݣ��ҵ������ڶ�����е����
	//����_vertex_valΪ���������
	//����ֵΪ�������������δ�ҵ����򷵻�-1
	template<typename EdgeType, typename VertexType>
	inline int algraph<EdgeType, VertexType>::locate_vertex(const VertexType &_vertex_val) {
		for (int i = 0; i < vertex_num; ++i) {
			if (vertex_table[i].value == _vertex_val)
				return i;
		}
		return -1;
	}

	//���ݶ������ţ�ȡ�ö��������
	//����_vertex_orderΪ������ţ�����_vertex_val���ڷ��ض����ֵ
	template<typename EdgeType, typename VertexType>
	inline bool algraph<EdgeType, VertexType>::get_vertex_data(int _vertex_order, VertexType &_vertex_val) {
		if (_vertex_order<0 || _vertex_order>MAX_NUM)
			return false;
		_vertex_val = vertex_table[_vertex_order].value;
		return true;

	}

	//���ݶ������ţ����ö��������
	//����_vertex_orderΪ������ţ�����_vertex_val�������ö����ֵ
	template<typename EdgeType, typename VertexType>
	inline bool algraph<EdgeType, VertexType>::set_vertex_data(int _vertex_order, const VertexType &_vertex_val) {
		if (_vertex_order<0 || _vertex_order>MAX_NUM)
			return false;
		vertex_table[_vertex_order].value = _vertex_val;
		return true;
	}

	template<typename EdgeType, typename VertexType>
	bool algraph<EdgeType, VertexType>::get_vertex_value(VertexType& result, int v) {
		if (v >= 0 && v < vertex_num) {
			result = vertex_table[v].value;
			return true;
		}
		return false;
	}

	template<typename EdgeType, typename VertexType>
	bool algraph<EdgeType, VertexType>::get_weight(EdgeType& result, int v1, int v2) {
		edge_node<EdgeType> *p;
		if (v1 >= 0 && v1 < vertex_num && v2 >= 0 && v2 < vertex_num) {
			p = vertex_table[v1].first_edge_node;
			while (p != nullptr) {
				if (p->vertex_index == v2) {
					result = p->weight;
					return true;
				}
				p = p->next;
			}
		}
		return false;
	}

	template<typename EdgeType, typename VertexType>
	int algraph<EdgeType, VertexType>::getvertex_indexposition(int v) {
		edge_node<EdgeType> *p;
		if (v >= 0 && v < vertex_num) {
			p = vertex_table[v].first_edge_node;
			if (p != nullptr) return p->vertex_index;
		}
		return -1;
	}


	template<typename EdgeType, typename VertexType>
	int algraph<EdgeType, VertexType>::get_next_vertex_index(int v1, int v2) {
		edge_node<EdgeType> *p;
		if (v1 >= 0 && v2 >= 0 && v1 < vertex_num && v2 < vertex_num) {
			p = vertex_table[v1].first_edge_node;
			while (p != nullptr) {
				if (p->vertex_index == v2 && p->next != nullptr)
					return p->next->vertex_index;
				else p = p->next;
			}
		}
		return -1;
	}

	//��ͼ�в���һ������
	//����_vertex_valΪҪ����������
	template<typename EdgeType, typename VertexType>
	bool algraph<EdgeType, VertexType>::insert_vertex(const VertexType& _vertex_val) {
		//������ڵĶ�������Ѵﵽ���ֵ���򷵻�false
		if (vertex_num >= MAX_NUM) {
			std::cerr << "exceed max vertex limit!" << std::endl;
			return false;
		}
		////�ж���ͬ�Ķ����Ƿ���ڡ������ڣ��򷵻�false
		//for (int i = 0; i < vertex_num; ++i) {
		//	if (vertex_table[i].value == _vertex_val)
		//		return false;
		//}
		//����һ������
		vertex_table[vertex_num].value = _vertex_val;
		vertex_table[vertex_num++].first_edge_node = nullptr;
		return true;
	}

	//��ͼ��ɾ��һ������
	//����_vertex_valΪҪɾ����������ӱ��е����
	template<typename EdgeType, typename VertexType>
	bool algraph<EdgeType, VertexType>::delete_vertex(const VertexType &_vertex_val)
	{
		//_vertex_indexΪ�õ������
		int _vertex_index = locate_vertex(_vertex_val);
		//�����ҵ����к�Ϊ_vertex_val�Ķ��㡣���û���ҵ����򷵻�false
		if (_vertex_index == -1)
			return false;
		//�������е�,�����Щ�������ӱ��а�����Ҫɾ���Ķ��㣬���Ƴ�
		for (int i = 0; i < vertex_num; ++i) {
			if (i == _vertex_index) {	//������صĶ��������ֵ�Ѱ���
				vertex_table[i].remove_edge(_vertex_val);//��ɾ��������
				edge_num--;
			}
		}
		//ɾ�����Ϊ_vertex_index�Ķ������ӱ�
		vertex_table[_vertex_index].clear_edge_list();
		//����������е���������˳�򣬲����ܵĶ�������һ
		for (int i = _vertex_index; i < vertex_num; ++i)
			vertex_table[i] = vertex_table[i + 1];
		--vertex_num;
		return true;

	}

	//��ͼ�в���һ����
	//����_weightΪ������ߵ�Ȩֵ��
	//����_vertex_val1��_vertex_val2Ϊ������ߵ����������ֵ
	template<typename EdgeType, typename VertexType>
	bool algraph<EdgeType, VertexType>::insert_edge(const EdgeType& _weight, const VertexType& _vertex_val1, const VertexType& _vertex_val2) {
		//edge_node<EdgeType> *p, *q;
		////���жϲ����Ƿ����
		//if (_vertex_val1 >= 0 && _vertex_val2 >= 0 && _vertex_val1 < vertex_num && _vertex_val2 < vertex_num) {
		//	p = q = vertex_table[_vertex_val1].first_edge_node;
		//	//����ڽӱ���׽��Ϊ�գ�����һ���ڽӱ��׽�㣬�붥������
		//	if (p == nullptr) {
		//		vertex_table[_vertex_val1].first_edge_node = new edge_node<EdgeType>(_vertex_val2, _weight);
		//		return true;
		//	}
		//	while (p != nullptr) {
		//		//������ڽӱ�����Ѿ�����ֵΪ_vertex_val2�ĵ㣬�򷵻�false
		//		if (p->vertex_index == _vertex_val2) {
		//			std::cerr << "edge exists , cannot insert!" << std::endl;
		//			return false;
		//		}
		//		//����ƶ�ָ�룬�ҵ�ֵΪ_vertex_val1��_vertex_val2��������
		//		q = p;
		//		p = p->next;
		//	}
		//	//���Ϊ����ͼ����ֻ��Ҫ����һ����
		//	q->next = new edge_node<EdgeType>(_vertex_val2, _weight);
		//���Ϊ����ͼ������Ҫ����һ�������ӱ�������һ����
		vertex_table[_vertex_val1].append_edge(_vertex_val2, _weight);
		if (graph == UDG || graph == UDN) {
			vertex_table[_vertex_val2].append_edge(_vertex_val1, _weight);
		}
		edge_num++;
		return true;
	}

	//��ͼ��ɾ��һ����
	//����_vertex_val1��_vertex_val2ΪҪɾ����������������
	template<typename EdgeType, typename VertexType>
	bool algraph<EdgeType, VertexType>::delete_edge(const VertexType &, const VertexType &)
	{
		
	}

	//���ݶ�����ţ�ȡ�ö����ֵ
	//����_vertex_indexΪ������ţ�����_vertex_value���ڷ��ض�������
		template<typename EdgeType, typename VertexType>
		bool algraph<EdgeType, VertexType>::get_vertex(int _vertex_index, VertexType & _vertex_val)
		{
			if (_vertex_index<0 || _vertex_index>MAX_NUM)
				return false;
			_vertex_val = vertex_table[_vertex_index].value;
			return true;
		}

		template<typename EdgeType, typename VertexType>
		void algraph<EdgeType, VertexType>::show()
		{
			edge_node<EdgeType> *p;
			for (int i = 0; i < vertex_num; ++i) {
				p = vertex_table[i].first_edge_node;
				std::cout << "[" << i << ":" << vertex_table[i].value << "]";
				while (p != nullptr) {
					std::cout << "--" << p->weight << "-->" << "[" << p->vertex_index << "]";
					p = p->next;
				}
				std::cout << std::endl;
			}
		}
	}

#endif