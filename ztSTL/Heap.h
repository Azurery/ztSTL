#ifndef _ZT_HEAP_H
#define _ZT_HEAP_H

#include "Iterator.h"
/*�˶�Ϊ���ѣ�����״Ϊ��ȫ������
*/
namespace ztSTL {
	typedef iterator_traits<random_access_iterator_tag>::difference_type Distance;
	//����push_heapʱ����Ԫ��Ӧ���Ѿ����ڵײ���������׶�
	//push_heap���������������������ֱ����heap�ײ�������vector����ͷβ
	template <typename Randam_Acess_Iterator>
	inline void push_heap(Randam_Acess_Iterator first,
		Randam_Acess_Iterator last) {
		//��ǰ����ֵ
		auto value = value_type(first);
		//��������β�ˣ��˼���һ�����
		//������˵Ľ���������0
		Distance top_index = difference_type(0);
		/*������ĩβ�Ľ���������
		��Ϊfirst��ָ���Ǹ�Ԫ�ز���heap�����Ԫ�أ����Ծ���Ҫ��ȥ1
		*/
		Distance low_index = difference_type((last - first) - 1);
		//�ҳ�������ĸ��������
		Distance parent = (low_index-1) / 2;
		/*�жϵ�ǰ����ֵ�Ƿ�����丸��㣬����ǣ��򸸽�������ƶ���
		�����õ�ǰ���Ϊ����㣬���������жϣ�ֱ����ֵС�ڸ�����ֵ���ߴﵽheap�Ķ���
		*/
		while (low_index > top_index && *parent < value) {
			*low_index = *parent;
			low_index = parent;
			parent = (low_index - 1) / 2;
		}
		//�ҵ����ʵ�λ�ã����ó���ȷ��ֵ
		*low_index = value;
	}

	//�����ѣ�ά�ֶѵ�����
	template <typename Randam_Acess_Iterator,typename Distance,typename T>
	void adjust_heap(Randam_Acess_Iterator first,Distance parent_index,
					Distance heap_size,T value) {
		Distance top_index = parent_index;
		//�������к��ӽ��
		Distance rchild_index = 2 * (parent_index)+2;

		while (rchild_index < heap_size) {
			//�Ƚ������ӽڵ��ֵ�Ĵ�С������right_child����ϴ�ֵ
			if (*rchild_index < *(rchild_index - 1) {
				rchild_index--;
				*parent_index = *rchild_index;
				rchild_index = 2 * (rchild_index + 1);
			}
		}
		//ֻ�����ӽ�㣬û�����ӽ�㡣�����ӽ���Ƶ�������λ��
		if (rchild_index == heap_size) {
			*parent_index = *(rchild_index--);
			parent_index = rchild_index - 1;
		}
		*parent_index = value;
	}

	//������


	
}
#endif