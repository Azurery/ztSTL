#ifndef _ZT_DEQUE_H_
#define _ZT_DEQUE_H_
#include "Iterator.h"

/*deque���ڲ�ʵ��ԭ��
˫�˶��е����ݱ���ʾΪһ���ֶ����飬�����е�Ԫ�طֶδ���һ������С�̶��������У���������
����Ҫά��һ�������Щ�����׵�ַ����������

	��������  
			 |		|     �ֶ�����
			 |------|	  _____________________
			 |		|��������>|		|      |	  |	
			 |------|	  ---------------------
			 |		|     _____________________
			 |------|	  |		|      |	  |	
			 |		|��������>_____________________
			 |------|

���ڷֶ�����Ĵ�С�ǹ̶��ģ��������ǵ��׵�ַ��������������������У���˿��Զ������������ʣ�
��Ч�ʱ�vector�ͺܶ�

1.�����˼�����Ԫ��ʱ�������һ�˵ķֶ�����δ���������ֱ�Ӽ��롣
�������һ�˵ķֶ�����������ֻ�贴���µķֶ����飬���Ѹ÷ֶ�����ĵ�ַ���뵽���������м��ɡ�
�����������������Ҫ�����е�Ԫ�ؽ����ƶ���������˫�˶��е����˼���Ԫ���µ�Ԫ�ض����нϸߵ�Ч��
2.�����˫�˶������������˵�Ԫ��ʱ�����ڲ���Ҫ����Ԫ�ص��ƶ���Ч��Ҳ�Ƿǳ��ߵ�
3.˫�˶����м����Ԫ��ʱ����Ҫ������㵽ĳһ��֮�������Ԫ������������һ���ƶ�.�����λ��Խ����,Ч��Խ��

ע��:�ڳ�����β���˵�����λ�ò����ɾ��Ԫ��,�����ᵼ��ָ��dequeԪ�ص��κ�pointer��reference��iteratorʧЧ
*/
namespace ztSTL {
	template <typename T>
	class deque_iterator :public iterator<bidirectional_iterator_tag,T> {
	private:
		template <typename T>
		friend class deque;
	private:
		typedef deque_iterator<T> iterator;
		typedef T** segment_pointer;
	private:
		pointer cur;
		pointer 

	};

	template <typename T>
	class deque {
	private:
		typedef size_t size_type;
		typedef T value_type;
		typedef T* pointer;
		typedef pointer* segment_ponter;//Ԫ�ص�ָ���ָ��
	private:
		segment_ponter segment;	//ָ��segment��segment��Ϊ�ֶ����飬���е�ÿһ��Ԫ�ض���һ��ָ�루��Ϊ��㣩��ָ��һ����������
		size_type segment_size;	//segment�������ɵ�ָ����Ŀ
	};
}




#endif

