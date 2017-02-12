#ifndef _ZT_GRAPH_H_
#define _ZT_GRAPH_H_

#include <iostream>

namespace ztSTL {
	const int MAX_NUM = 20;

	//前向声明
	template <typename EdgeType, typename VertexType> class algraph;
	template <typename EdgeType, typename VertexType> class vertex_node;

	//定义顶点邻接表的结点结构
	template <typename EdgeType>
	class edge_node {
		template<typename type1, typename type2> friend class vertex_node;
		template<typename type1, typename type2> friend class algraph;
	private:
		int vertex_index;		//该边中的邻接顶点在顶点表中的序号
		EdgeType weight;//该边的权重
		edge_node *next;//指向下一条边的指针
		edge_node() :next(nullptr) {}
		edge_node(int v, const EdgeType& w) :vertex_index(v), weight(w), next(nullptr) {}
	};

	//顶点结点类
	template <typename EdgeType, typename VertexType>
	class vertex_node {
		friend class algraph<EdgeType, VertexType>;
	private:
		VertexType value;		//顶点的数据
		edge_node<EdgeType> *first_edge_node;//顶点邻接表的首结点指针
		vertex_node() :first_edge_node(nullptr) {}
	public:
		void clear_edge_list();			//删除该顶点的邻接表
		bool append_edge(int, int = 0);//在该顶点的邻接表中加入一条边
		bool remove_edge(int);	//在该顶点的邻接表中删除一条边
	};
	//清空一个顶点的邻接链表，释放邻接表的各结点
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
	//在该顶点的邻接表中加入一条边
	//参数_vertex为加入边的邻接顶点序号,_weight为加入边的权值
	template <typename EdgeType, typename VertexType>
	bool vertex_node<EdgeType, VertexType>::append_edge(int _vertex_index, int _weight) {
		edge_node<EdgeType>* cur = first_edge_node;
		edge_node<EdgeType>* temp = nullptr;
		//找到邻接链表的末尾结点
		while (cur != nullptr) {
			if (cur->vertex_index == _vertex_index)
				return false;
			temp = cur;
			cur = cur->next;
		}
		//在邻接表的最后加上一条边
		edge_node<EdgeType>* new_node = new edge_node<EdgeType>(_vertex_index, _weight);
		//如果链表为空，则将头结点置为新结点
		if (temp == nullptr)
			first_edge_node = new_node;
		else
			temp->next = new_node;
		return true;
	}
	//在顶点的邻接表中删除一条边
	template <typename EdgeType, typename VertexType>
	bool vertex_node<EdgeType, VertexType>::remove_edge(int _vertex_val) {
		edge_node* cur = first_edge_node;
		edge_node* temp = nullptr;
		//遍历领接表，如果找到这条边，则将其删除
		while (cur) {
			if (cur->vertex_index == _vertex_val) {
				//如果要删除的是头结点
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

	/*图的邻接表定义
	VertexType是顶点的数据类型，如果VertexType不是简单的数据类型，在定义VertexType时，
	必须重载==运算符用于判断两个顶点数据是否相等
	*/
	template<typename EdgeType, typename VertexType>
	class algraph {
	private:
	public:
		//图的四中种类
		enum algraph_type {
			DG,		//有向图
			DN,		//有向网
			UDG,	//无向图
			UDN		//无向网
		};
	private:
		vertex_node<EdgeType, VertexType> *vertex_table; //顶点表
		int vertex_num;	//顶点个数
		int edge_num;	//边数
		algraph_type graph;//图的类型
	public:
		algraph() :vertex_table(nullptr), vertex_num(0), edge_num(0) {}
		algraph(VertexType *v, int num = MAX_NUM, algraph_type = UDG);
		~algraph();

		int locate_vertex(const VertexType&);  //根据顶点的数据，找到顶点在顶点表中的序号
		bool get_vertex_data(int, VertexType&);		//根据序号，取得顶点的数据
		bool set_vertex_data(int, const VertexType&);//根据序号，设置顶点的数据	
		bool insert_vertex(const VertexType&);		//插入一个顶点
		bool delete_vertex(const VertexType&);	//删除一个顶点
		bool insert_edge(const EdgeType&, const VertexType&, const VertexType&);	//插入一条边
		bool delete_edge(const VertexType&, const VertexType&);
		int get_first_vertex_index(int);
		bool get_edge(int, int, edge_node<EdgeType>*&);//根据顶点序号，取得两顶点之间的边		
		bool get_vertex(int _vertex_index, VertexType& _vertex_val);
		bool empty() { return vertex_num == 0; }
		inline int get_vertex_nums() { return vertex_num; } //取得图中的顶点数目
		inline int get_edge_nums() { return edge_num; }		//取得图中的边数

		bool get_vertex_value(VertexType& result, int v);
		bool get_weight(EdgeType& result, int v1, int v2);
		int getvertex_indexposition(int v);
		int get_next_vertex_index(int v1, int v2);
		void bfs(void(*visit)(const VertexType&));
		void dfs(void(*visit)(const VertexType&));
		void show();
	};
	//默认为无向图UDG
	template<typename EdgeType, typename VertexType>
	algraph<EdgeType, VertexType>::algraph(VertexType *v, int num, algraph_type _graph) :
		vertex_num(0), edge_num(0), graph(_graph) {
		vertex_table = new vertex_node<EdgeType, VertexType>[num];
		for (int i = 0; i < num; ++i)
			insert_vertex(v[i]);
	}
	//析构函数
	template<typename EdgeType, typename VertexType>
	algraph<EdgeType, VertexType>::~algraph() {
		edge_node<EdgeType> *p;
		for (int i = 0; i < vertex_num; ++i) {
			//p指向邻接表的头结点
			p = vertex_table[i].first_edge_node;
			while (p != nullptr) {
				vertex_table[i].first_edge_node = p->next;
				delete p;
				p = vertex_table[i].first_edge_node;
			}
		}
		delete[] vertex_table;
	}

	//根据顶点的数据，找到顶点在顶点表中的序号
	//参数_vertex_val为顶点的数据
	//返回值为顶点的索引。若未找到，则返回-1
	template<typename EdgeType, typename VertexType>
	inline int algraph<EdgeType, VertexType>::locate_vertex(const VertexType &_vertex_val) {
		for (int i = 0; i < vertex_num; ++i) {
			if (vertex_table[i].value == _vertex_val)
				return i;
		}
		return -1;
	}

	//根据顶点的序号，取得顶点的数据
	//参数_vertex_order为顶点序号；参数_vertex_val用于返回顶点的值
	template<typename EdgeType, typename VertexType>
	inline bool algraph<EdgeType, VertexType>::get_vertex_data(int _vertex_order, VertexType &_vertex_val) {
		if (_vertex_order<0 || _vertex_order>MAX_NUM)
			return false;
		_vertex_val = vertex_table[_vertex_order].value;
		return true;

	}

	//根据顶点的序号，设置顶点的数据
	//参数_vertex_order为顶点序号；参数_vertex_val用于设置顶点的值
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

	//根据序号，取得v1(相对于v2)的下一个邻接顶点序号
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

	//在图中插入一个顶点
	//参数_vertex_val为要插入点的数据
	template<typename EdgeType, typename VertexType>
	bool algraph<EdgeType, VertexType>::insert_vertex(const VertexType& _vertex_val) {
		//如果存在的顶点个数已达到最大值，则返回false
		if (vertex_num >= MAX_NUM) {
			std::cerr << "exceed max vertex limit!" << std::endl;
			return false;
		}
		////判断相同的顶点是否存在。若存在，则返回false
		//for (int i = 0; i < vertex_num; ++i) {
		//	if (vertex_table[i].value == _vertex_val)
		//		return false;
		//}
		//增加一个顶点
		vertex_table[vertex_num].value = _vertex_val;
		vertex_table[vertex_num++].first_edge_node = nullptr;
		return true;
	}

	//在图中删除一个顶点
	//参数_vertex_val为要删除顶点在领接表中的序号
	template<typename EdgeType, typename VertexType>
	bool algraph<EdgeType, VertexType>::delete_vertex(const VertexType &_vertex_val)
	{
		//_vertex_index为该点的索引
		int _vertex_index = locate_vertex(_vertex_val);
		//首先找到序列号为_vertex_val的顶点。如果没有找到，则返回false
		if (_vertex_index == -1)
			return false;
		//遍历所有点,如果这些顶点的领接表中包含了要删除的顶点，则移除
		for (int i = 0; i < vertex_num; ++i) {
			if (i == _vertex_index) {	//如果返回的顶点的索引值已包含
				vertex_table[i].remove_edge(_vertex_val);//则删除该条边
				edge_num--;
			}
		}
		//删除序号为_vertex_index的顶点的领接表
		vertex_table[_vertex_index].clear_edge_list();
		//调整顶点表中的其余各点的顺序，并将总的顶点数减一
		for (int i = _vertex_index; i < vertex_num; ++i)
			vertex_table[i] = vertex_table[i + 1];
		--vertex_num;
		return true;

	}

	//在图中插入一条边
	//参数_weight为欲插入边的权值；
	//参数_vertex_val1、_vertex_val2为欲插入边的两个顶点的值
	template<typename EdgeType, typename VertexType>
	bool algraph<EdgeType, VertexType>::insert_edge(const EdgeType& _weight, const VertexType& _vertex_val1, const VertexType& _vertex_val2) {
		//edge_node<EdgeType> *p, *q;
		////先判断参数是否合理
		//if (_vertex_val1 >= 0 && _vertex_val2 >= 0 && _vertex_val1 < vertex_num && _vertex_val2 < vertex_num) {
		//	p = q = vertex_table[_vertex_val1].first_edge_node;
		//	//如果邻接表的首结点为空，则构造一个邻接表首结点，与顶点相连
		//	if (p == nullptr) {
		//		vertex_table[_vertex_val1].first_edge_node = new edge_node<EdgeType>(_vertex_val2, _weight);
		//		return true;
		//	}
		//	while (p != nullptr) {
		//		//如果在邻接表表中已经存在值为_vertex_val2的点，则返回false
		//		if (p->vertex_index == _vertex_val2) {
		//			std::cerr << "edge exists , cannot insert!" << std::endl;
		//			return false;
		//		}
		//		//向后移动指针，找到值为_vertex_val1、_vertex_val2的两个点
		//		q = p;
		//		p = p->next;
		//	}
		//	//如果为有向图，则只需要插入一条边
		//	q->next = new edge_node<EdgeType>(_vertex_val2, _weight);
		//如果为无向图，则需要在另一顶点的领接表中增加一条边
		vertex_table[_vertex_val1].append_edge(_vertex_val2, _weight);
		if (graph == UDG || graph == UDN) {
			vertex_table[_vertex_val2].append_edge(_vertex_val1, _weight);
		}
		edge_num++;
		return true;
	}

	//在图中删除一条边
	//参数_vertex_val1、_vertex_val2为要删除的两个顶点数据
	template<typename EdgeType, typename VertexType>
	bool algraph<EdgeType, VertexType>::delete_edge(const VertexType &_vertex_val1, const VertexType &_vertex_val2)
	{
		//找到两个顶点在顶点表中的序号_vertex_index1、_vertex_index2
		//两个顶点只要有一个在图中的顶点表中找不到就返回
		int v1 = locate_vertex(_vertex_val1);
		int v2 = locate_vertex(_vertex_val2);
		if (v1 == -1 || v2 == -1) {
			return false;
		}
		//在第一个顶点的邻接表中删除一条边
		vertex_table[v1].remove_edge(v2);
		//如果为无向图，则需要删除另一个顶点的领接表的一条边
		if (graph == UDG || graph == UDN) {
			vertex_table[v2].remove_edge(v1);
		}
		edge_num--;
		return true;
	}

	//取得图中某一个顶点的第一个领接顶点序号
	template<typename EdgeType, typename VertexType>
	int algraph<EdgeType, VertexType>::get_first_vertex_index(int _vertex_val)
	{
		if (_vertex_val<0 || _vertex_val>vertex_num) {
			return -1;
		}
		//如果该顶点在邻接表中的头结点不存在
		if (vertex_table[_vertex_val].first_edge_node == nullptr) {
			return -1;
		}
		else
			return vertex_table[_vertex_val].first_edge_node->vertex_index;
	}

	template<typename EdgeType, typename VertexType>
	bool algraph<EdgeType, VertexType>::get_edge(int _vertex_index1, int _vertex_index2, edge_node<EdgeType>*& _edge)
	{
		if (_vertex_index1<0 || _vertex_index1>vertex_num) {
			return false;
		}
		if (_vertex_index2<0 || _vertex_index2>vertex_num) {
			return false;
		}
		_edge = first_edge_node->next;

	}

	//根据顶点序号，取得顶点的值
	//参数_vertex_index为顶点序号；参数_vertex_value用于返回顶点数据
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