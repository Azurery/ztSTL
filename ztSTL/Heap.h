#ifndef _ZT_HEAP_H
#define _ZT_HEAP_H

#include "Iterator.h"
/*此堆为最大堆，其形状为完全二叉树
*/
namespace ztSTL {
	typedef iterator_traits<random_access_iterator_tag>::difference_type Distance;
	//调用push_heap时，新元素应该已经置于底部容器的最底端
	//push_heap接受两个迭代器参数，分别代表heap底部容器（vector）的头尾
	template <typename Randam_Acess_Iterator>
	inline void push_heap(Randam_Acess_Iterator first,
		Randam_Acess_Iterator last) {
		//当前结点的值
		auto value = value_type(first);
		//容器的最尾端，此即第一个结点
		//堆中最顶端的结点的索引：0
		Distance top_index = difference_type(0);
		/*堆中最末尾的结点的索引：
		因为first所指的那个元素不是heap的组成元素，所以距离要减去1
		*/
		Distance low_index = difference_type((last - first) - 1);
		//找出待处理的父结点索引
		Distance parent = (low_index-1) / 2;
		/*判断当前结点的值是否大于其父结点，如果是，则父结点向下移动，
		并设置当前结点为父结点，继续向上判断，直到其值小于父结点的值或者达到heap的顶端
		*/
		while (low_index > top_index && *parent < value) {
			*low_index = *parent;
			low_index = parent;
			parent = (low_index - 1) / 2;
		}
		//找到合适的位置，设置成正确的值
		*low_index = value;
	}

	//调整堆，维持堆的秩序
	template <typename Randam_Acess_Iterator,typename Distance,typename T>
	void adjust_heap(Randam_Acess_Iterator first,Distance parent_index,
					Distance heap_size,T value) {
		Distance top_index = parent_index;
		//父结点的有孩子结点
		Distance rchild_index = 2 * (parent_index)+2;

		while (rchild_index < heap_size) {
			//比较左右子节点的值的大小，并以right_child代表较大值
			if (*rchild_index < *(rchild_index - 1) {
				rchild_index--;
				*parent_index = *rchild_index;
				rchild_index = 2 * (rchild_index + 1);
			}
		}
		//只有左子结点，没有右子结点。将左子结点移到父结点的位置
		if (rchild_index == heap_size) {
			*parent_index = *(rchild_index--);
			parent_index = rchild_index - 1;
		}
		*parent_index = value;
	}

	//创建堆


	
}
#endif