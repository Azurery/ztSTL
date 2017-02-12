/*traits技术可以用来获得一个类型的相关信息
假设有如下一个泛型的迭代器，其中类型参数T为迭代器所指向的类型
template<typename T>
class myIterator{
....
};
当我们使用myIterator时，怎样才能获知它所指向的元素的类型呢？我们可以为这个类加入一个内嵌类型：
template<typename T>
class myIterator{
	typedef T value_type；
....
};
这样当我们使用myIterator类型时，可以通过myIterator::value_type来获得相应的myIterator
所指向的类型。

现在设计一个算法，使用上述信息：
template <typename T>
typename myIterator<T>::value_type
Foo(myIterator<T> i){
....
}
此处定义了一个函数Foo，他的返回值为参数i所指向的类型——就是T，那么我们为什么要兴师动众的使用
那个value_type呢？那是因为，当我们希望修改Foo函数，使它能够适应所有类型的迭代器时，我们可以
这样写:
template <typename Iterator>  //此处的Iterator可以是任意类型的迭代器
typename I::value_type Foo(Iterator i){
....
}
现在，任意定义了value_type内嵌类型的迭代器都可以作为Foo的参数了，并且Foo的返回值的类型将与相
应迭代器所指的元素的类型一致。

原生指针也完全可以作为迭代器来使用，然而我们显然没有办法来为原生指针添加一个value_type的内嵌类型，
如此一来，我们的Foo函数就不能使用原生指针了。
因此，我们便使用类信息萃取机traits

我们可以不使用myIterator的value_type，而是通过另一个类来把这个信息提取出来：
template <typename T>
class traits{
	typedef typename T::value_type value_type;
};
这样，我们可以通过traits<myIterator>::value_type来获得myIterator的value_type，于是我们把
Foo函数改写为：
template <typename Iterator>
typename traits<Itetator>::value_type(Iterator I){
....
}
然而，即使这样，原生指针的问题任然没有解决，因为traits类一样没有办法获得原生指针的相关信息。于是
我们使用c++的特例化：
template <typename T>
class traits<T*>{
	typedef typename T value_type;
};
通过上面这个traits的特例化版本，我们陈述了一个事实：一个T*类型的指针所指向的元素的类型为T
如此一来，函数Foo便可以完全使用于原生指针了.
e.g. int* p;
	.....
	int i=Foo(p);
	traits会自动推导出p所指元素的类型为int，从而fo正确返回

Conclusion.整个过程为：内嵌类型->traits类->模板特例化->可萃取原生指针的value_type

*/


/*1.设计适当的型别，是迭代器的责任
2.设计适当的迭代器，则是容器的责任。唯有容器本身，才知道该设计出怎样的迭代器来遍历自己，
并执行迭代器的各种行为（前进、后退、取值......）
3.对于算法，全完独立于容器和迭代器之外的自行发展，只要设计时以迭代器为对外接口就行


迭代器iterator是一种smart pointer
迭代器最重要的工作是对operator*和operator->进行重载

input iterator
				-->forward iterator-->bidirectional iterator-->random access iterator
output iterator
看似这几个迭代器像是继承关系，但实际上在STL中，这些并不是通过继承关联的
这些只不过是一些符合条件的集合。这样的好处是少去了一个特殊的基类（input iterator)
其次，使得内建类型指针可以成为iterator

只要明白iterator是满足某些特别的功能的集合(包括类和内建对象),就不会觉得是继承了

*/
#ifndef _ZT_ITERATOR_H_
#define _ZT_ITERATOR_H_
#include <cstdlib>

/*以class来定义迭代器的各种分类标签，不仅可以促进重载机制的成功运行，另一个好处是，
通过继承，我们可以不必再写“单纯只做传递调用”的函数*/
namespace ztSTL {
	/*输入迭代器(input iterator 只读)：工作方式就像输入流
	.取出其所指向的值
	.访问下一个元素
	.判断是否到达了最后一个元素
	.可以复制
	其支持的操作：*p,++p,p++,p!=q,p==q.
	凡是支持这五个操作符的类都可以称作是input iterator*/
	struct input_iterator_tag {};

	/*输出迭代器(output iterator 只读):作方式就像输出流
	能对其指向的序列进行写操作，其与input iterator不相同的
	就是*p所返回的值允许修改，而不一定要读取。而input iterator
	只允许读取，不允许修改
	  支持的操作和input iterator一样
	*/
	struct output_iterator_tag {};

	/*前向迭代器(forward iterator 前向移动读取):相当于输入和输出的迭代器的结合
	其*p既可以访问元素，也可以修改元素
	其支持的操作为*p,++p,p++,p!=q,p==q*/
	struct forward_iterator_tag :public input_iterator_tag {};

	/*双向迭代器(bidirectional iterator 双向移动读取):在前向迭代器上更近一步
	其支持的操作有*p,++p,p++,p!=q,p==q，--p,p--*/
	struct bidirectional_iterator_tag :public forward_iterator_tag {};

	/*随机存取迭代器(random access iterator 随机读取):其在双向迭代器(bidirectional iterator)的功能上，
	允许随机访问序列的任意值。显然，指针就是一个这样的一个迭代器
	其支持的操作：
	1.可以判断是否到达结尾(a==b或a!b)
	2.可以双向递增或递减(--a或++a)
	3.可以比较大小(a<b或a>b或a>=b...etc)
	4.支持算数运算（a+n)
	5.支持随机访问(a[n])
	6.支持符合运算(a+=n)
	*/
	struct random_access_iterator_tag :public bidirectional_iterator_tag {};

	/*如果每个新设计的迭代器都继承iterator，就可保证STL所需要的规范
	iterator class不包含任何成员，纯粹只是型别定义，所以继承它并不会招致任何额外负担。
	由于后三个参数皆有默认值，故新迭代器只需提供前两个参数即可
	*/
	template <class Category,
	class T,
	class Distance = ptrdiff_t,
	class Pointer = T*,
	class Reference = T&>
	struct iterator {
		typedef Category	iterator_category;  //iterator_category表示迭代器的分类。任何一种迭代器，都属于其中的一种分类
		typedef T			value_type;	//value_type是所指对象类型，内嵌型别声明(nested type)
		typedef Distance    difference_type;	//difference_type是一种常用的迭代器类型，用来表示两个迭代器之间的距离
		typedef Pointer		pointer;//迭代器所指的数据，不允许修改，即可以当右值
		typedef	Reference   reference;
	};
	/*partial specialization（特例化）
	一个特例化版本就是模板的一个独立的定义，在其中一个或者多个模板参数被指定为特定的类型
	换句话说，我们可以在泛化操作设计中提供一个特例化版本
	-----所谓partial specialization的意思是提供一份template定义式，而其本身认为templated
	这可以解决“原生指针并非class，因此无法为它们定义内嵌类型”的问题，现在我们可以针对“迭代器之template参数为指针”者，设计特例化的迭代器。
	.该class template专门用来“萃取”迭代器的特性
	定义一个iterator——traits，其意义是如果I有自己定义的value_type，那么通过这个traits的作用，萃取出来的value_type就是I：：value_type

	例如，原始指针int*虽然不是一种class type，也可以通过traits取其value type
	1.traits所扮演的是“特性萃取机”角色，萃取各个迭代器的特性。所谓的迭代器特性，指的是迭代器的相应型别。
	2.若要这个“特性萃取机”traits能够有效运作，每一个迭代器必须遵循约定，自行以内嵌型别定义的方式定义出相应型别。
	若不遵循这个约定，将不能兼容STL
	3.通过class template partial specialization的作用，不论是原生指针或class-type iterators，都可以让外界方便地取其相应型别

	凡是原生指针，都没有能力定义自己的相应型别
	凡是class-type iterators，都有能力（且应该）定义自己的相应型别
	*/
	//“萃取机”traits
	template <class Iterator>
	struct iterator_traits {
		typedef typename Iterator::iterator_category iterator_category;
		typedef typename Iterator::value_type value_type;
		//任何时候当我们需要任何迭代器的difference type，便可以这么写：
		//typename iterator_traits<Iterator>::difference_type;
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
	};

	//针对原生指针而设计的traits特例化
	template <class T>
	struct iterator_traits<T*> {
		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef ptrdiff_t					difference_type;
		typedef T*							pointer;
		typedef T&							reference;
	};

	//针对原生指向const的指针（pointer—to-const）的特例化
	template <class T>
	struct iterator_traits<const T*> {
		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef ptrdiff_t					difference_type;
		typedef const T*					pointer;
		typedef const T&					reference;
	};

	//返回迭代器类别
	template <class Iterator>
	inline typename iterator_traits<Iterator>::iterator_category
		iterator_category(const Iterator&) {
		typedef typename iterator_traits<Iterator>::iterator_category category;
		return category();
	}

	//返回表示迭代器距离的类型
	template <class Iterator>
	inline typename iterator_traits<Iterator>::difference_type* //函数返回的型别
		difference_type(const Iterator&) {
		return < static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
	}

	//返回迭代器所指对象的类型
	template <class Iterator>
	inline typename iterator_traits<Iterator>::value_type*
		value_type(const Iterator&) {
		return < static_cast<typename iterator_traits<Iterator>::value_type*>(0);
	}

	//如果编译器不支持模板特例化，就需要对所有迭代器类型提供定义
	template <class T, class Distance>
	struct input_iterator
	{
		typedef input_iterator_tag category;
		typedef T value_type;
		typedef Distance differcnce_type;
		typedef T* pointer;
		typedef T& reference;
	};

	struct output_iterator {
		typedef output_iterator_tag category;
		typedef void value_type;
		typedef void differcnce_type;
		typedef void pointer;
		typedef void reference;
	};

	template <class T, class Distance>
	struct forward_iterator {
		typedef forward_iterator_tag category;
		typedef T value_type;
		typedef Distance differcnce_type;
		typedef T* pointer;
		typedef T& reference;
	};

	template <class T, class Distance>
	struct bidirectional_iterator {
		typedef bidirectional_iterator_tag category;
		typedef T value_type;
		typedef Distance differcnce_type;
		typedef T* pointer;
		typedef T& reference;
	};

	template <class T, class Distance>
	struct random_access_iterator {
		typedef random_access_iterator_tag category;
		typedef T value_type;
		typedef Distance differcnce_type;
		typedef T* pointer;
		typedef T& reference;
	};


}
#endif