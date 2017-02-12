#ifndef _ZT_DEQUE_H_
#define _ZT_DEQUE_H_
#include "Iterator.h"

/*deque的内部实现原理：
双端队列的数据被表示为一个分段数组，容器中的元素分段存在一个个大小固定的数组中，此外容器
还需要维护一个存放这些数组首地址的索引数组

	索引数组  
			 |		|     分段数组
			 |------|	  _____________________
			 |		|————>|		|      |	  |	
			 |------|	  ---------------------
			 |		|     _____________________
			 |------|	  |		|      |	  |	
			 |		|————>_____________________
			 |------|

由于分段数组的大小是固定的，并且它们的首地址被连续存放在索引数组中，因此可以对其进行随机访问，
但效率比vector低很多

1.向两端加入新元素时，如果这一端的分段数组未满，则可以直接加入。
但如果这一端的分段数组已满，只需创建新的分段数组，并把该分段数组的地址加入到索引数组中即可。
无论哪种情况都不需要对已有的元素进行移动，所以在双端队列的两端加入元素新的元素都具有较高的效率
2.当算出双端队列中容器两端的元素时，由于不需要发生元素的移动，效率也是非常高的
3.双端队列中间插入元素时，需要将插入点到某一端之间的所有元素像容器的这一端移动.插入的位置越靠中,效率越低

注意:在除了首尾两端的其他位置插入和删除元素,都将会导致指向deque元素的任何pointer、reference、iterator失效
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
		typedef pointer* segment_ponter;//元素的指针的指针
	private:
		segment_ponter segment;	//指向segment，segment即为分段数组，其中的每一个元素都是一个指针（称为结点），指向一块索引数组
		size_type segment_size;	//segment可以容纳的指针数目
	};
}




#endif

