/*traits���������������һ�����͵������Ϣ
����������һ�����͵ĵ��������������Ͳ���TΪ��������ָ�������
template<typename T>
class myIterator{
....
};
������ʹ��myIteratorʱ���������ܻ�֪����ָ���Ԫ�ص������أ����ǿ���Ϊ��������һ����Ƕ���ͣ�
template<typename T>
class myIterator{
	typedef T value_type��
....
};
����������ʹ��myIterator����ʱ������ͨ��myIterator::value_type�������Ӧ��myIterator
��ָ������͡�

�������һ���㷨��ʹ��������Ϣ��
template <typename T>
typename myIterator<T>::value_type
Foo(myIterator<T> i){
....
}
�˴�������һ������Foo�����ķ���ֵΪ����i��ָ������͡�������T����ô����ΪʲôҪ��ʦ���ڵ�ʹ��
�Ǹ�value_type�أ�������Ϊ��������ϣ���޸�Foo������ʹ���ܹ���Ӧ�������͵ĵ�����ʱ�����ǿ���
����д:
template <typename Iterator>  //�˴���Iterator�������������͵ĵ�����
typename I::value_type Foo(Iterator i){
....
}
���ڣ����ⶨ����value_type��Ƕ���͵ĵ�������������ΪFoo�Ĳ����ˣ�����Foo�ķ���ֵ�����ͽ�����
Ӧ��������ָ��Ԫ�ص�����һ�¡�

ԭ��ָ��Ҳ��ȫ������Ϊ��������ʹ�ã�Ȼ��������Ȼû�а취��Ϊԭ��ָ�����һ��value_type����Ƕ���ͣ�
���һ�������ǵ�Foo�����Ͳ���ʹ��ԭ��ָ���ˡ�
��ˣ����Ǳ�ʹ������Ϣ��ȡ��traits

���ǿ��Բ�ʹ��myIterator��value_type������ͨ����һ�������������Ϣ��ȡ������
template <typename T>
class traits{
	typedef typename T::value_type value_type;
};
���������ǿ���ͨ��traits<myIterator>::value_type�����myIterator��value_type���������ǰ�
Foo������дΪ��
template <typename Iterator>
typename traits<Itetator>::value_type(Iterator I){
....
}
Ȼ������ʹ������ԭ��ָ���������Ȼû�н������Ϊtraits��һ��û�а취���ԭ��ָ��������Ϣ������
����ʹ��c++����������
template <typename T>
class traits<T*>{
	typedef typename T value_type;
};
ͨ���������traits���������汾�����ǳ�����һ����ʵ��һ��T*���͵�ָ����ָ���Ԫ�ص�����ΪT
���һ��������Foo�������ȫʹ����ԭ��ָ����.
e.g. int* p;
	.....
	int i=Foo(p);
	traits���Զ��Ƶ���p��ָԪ�ص�����Ϊint���Ӷ�fo��ȷ����

Conclusion.��������Ϊ����Ƕ����->traits��->ģ��������->����ȡԭ��ָ���value_type

*/


/*1.����ʵ����ͱ��ǵ�����������
2.����ʵ��ĵ��������������������Ρ�Ψ������������֪������Ƴ������ĵ������������Լ���
��ִ�е������ĸ�����Ϊ��ǰ�������ˡ�ȡֵ......��
3.�����㷨��ȫ������������͵�����֮������з�չ��ֻҪ���ʱ�Ե�����Ϊ����ӿھ���


������iterator��һ��smart pointer
����������Ҫ�Ĺ����Ƕ�operator*��operator->��������

input iterator
				-->forward iterator-->bidirectional iterator-->random access iterator
output iterator
�����⼸�����������Ǽ̳й�ϵ����ʵ������STL�У���Щ������ͨ���̳й�����
��Щֻ������һЩ���������ļ��ϡ������ĺô�����ȥ��һ������Ļ��ࣨinput iterator)
��Σ�ʹ���ڽ�����ָ����Գ�Ϊiterator

ֻҪ����iterator������ĳЩ�ر�Ĺ��ܵļ���(��������ڽ�����),�Ͳ�������Ǽ̳���

*/
#ifndef _ZT_ITERATOR_H_
#define _ZT_ITERATOR_H_
#include <cstdlib>

/*��class������������ĸ��ַ����ǩ���������Դٽ����ػ��Ƶĳɹ����У���һ���ô��ǣ�
ͨ���̳У����ǿ��Բ�����д������ֻ�����ݵ��á��ĺ���*/
namespace ztSTL {
	/*���������(input iterator ֻ��)��������ʽ����������
	.ȡ������ָ���ֵ
	.������һ��Ԫ��
	.�ж��Ƿ񵽴������һ��Ԫ��
	.���Ը���
	��֧�ֵĲ�����*p,++p,p++,p!=q,p==q.
	����֧����������������඼���Գ�����input iterator*/
	struct input_iterator_tag {};

	/*���������(output iterator ֻ��):����ʽ���������
	�ܶ���ָ������н���д����������input iterator����ͬ��
	����*p�����ص�ֵ�����޸ģ�����һ��Ҫ��ȡ����input iterator
	ֻ�����ȡ���������޸�
	  ֧�ֵĲ�����input iteratorһ��
	*/
	struct output_iterator_tag {};

	/*ǰ�������(forward iterator ǰ���ƶ���ȡ):�൱�����������ĵ������Ľ��
	��*p�ȿ��Է���Ԫ�أ�Ҳ�����޸�Ԫ��
	��֧�ֵĲ���Ϊ*p,++p,p++,p!=q,p==q*/
	struct forward_iterator_tag :public input_iterator_tag {};

	/*˫�������(bidirectional iterator ˫���ƶ���ȡ):��ǰ��������ϸ���һ��
	��֧�ֵĲ�����*p,++p,p++,p!=q,p==q��--p,p--*/
	struct bidirectional_iterator_tag :public forward_iterator_tag {};

	/*�����ȡ������(random access iterator �����ȡ):����˫�������(bidirectional iterator)�Ĺ����ϣ�
	��������������е�����ֵ����Ȼ��ָ�����һ��������һ��������
	��֧�ֵĲ�����
	1.�����ж��Ƿ񵽴��β(a==b��a!b)
	2.����˫�������ݼ�(--a��++a)
	3.���ԱȽϴ�С(a<b��a>b��a>=b...etc)
	4.֧���������㣨a+n)
	5.֧���������(a[n])
	6.֧�ַ�������(a+=n)
	*/
	struct random_access_iterator_tag :public bidirectional_iterator_tag {};

	/*���ÿ������Ƶĵ��������̳�iterator���Ϳɱ�֤STL����Ҫ�Ĺ淶
	iterator class�������κγ�Ա������ֻ���ͱ��壬���Լ̳��������������κζ��⸺����
	���ں�������������Ĭ��ֵ�����µ�����ֻ���ṩǰ������������
	*/
	template <class Category,
	class T,
	class Distance = ptrdiff_t,
	class Pointer = T*,
	class Reference = T&>
	struct iterator {
		typedef Category	iterator_category;  //iterator_category��ʾ�������ķ��ࡣ�κ�һ�ֵ����������������е�һ�ַ���
		typedef T			value_type;	//value_type����ָ�������ͣ���Ƕ�ͱ�����(nested type)
		typedef Distance    difference_type;	//difference_type��һ�ֳ��õĵ��������ͣ�������ʾ����������֮��ľ���
		typedef Pointer		pointer;//��������ָ�����ݣ��������޸ģ������Ե���ֵ
		typedef	Reference   reference;
	};
	/*partial specialization����������
	һ���������汾����ģ���һ�������Ķ��壬������һ�����߶��ģ�������ָ��Ϊ�ض�������
	���仰˵�����ǿ����ڷ�������������ṩһ���������汾
	-----��νpartial specialization����˼���ṩһ��template����ʽ�����䱾����Ϊtemplated
	����Խ����ԭ��ָ�벢��class������޷�Ϊ���Ƕ�����Ƕ���͡������⣬�������ǿ�����ԡ�������֮template����Ϊָ�롱�ߣ�����������ĵ�������
	.��class templateר����������ȡ��������������
	����һ��iterator����traits�������������I���Լ������value_type����ôͨ�����traits�����ã���ȡ������value_type����I����value_type

	���磬ԭʼָ��int*��Ȼ����һ��class type��Ҳ����ͨ��traitsȡ��value type
	1.traits�����ݵ��ǡ�������ȡ������ɫ����ȡ���������������ԡ���ν�ĵ��������ԣ�ָ���ǵ���������Ӧ�ͱ�
	2.��Ҫ�����������ȡ����traits�ܹ���Ч������ÿһ��������������ѭԼ������������Ƕ�ͱ���ķ�ʽ�������Ӧ�ͱ�
	������ѭ���Լ���������ܼ���STL
	3.ͨ��class template partial specialization�����ã�������ԭ��ָ���class-type iterators������������緽���ȡ����Ӧ�ͱ�

	����ԭ��ָ�룬��û�����������Լ�����Ӧ�ͱ�
	����class-type iterators��������������Ӧ�ã������Լ�����Ӧ�ͱ�
	*/
	//����ȡ����traits
	template <class Iterator>
	struct iterator_traits {
		typedef typename Iterator::iterator_category iterator_category;
		typedef typename Iterator::value_type value_type;
		//�κ�ʱ��������Ҫ�κε�������difference type���������ôд��
		//typename iterator_traits<Iterator>::difference_type;
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
	};

	//���ԭ��ָ�����Ƶ�traits������
	template <class T>
	struct iterator_traits<T*> {
		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef ptrdiff_t					difference_type;
		typedef T*							pointer;
		typedef T&							reference;
	};

	//���ԭ��ָ��const��ָ�루pointer��to-const����������
	template <class T>
	struct iterator_traits<const T*> {
		typedef random_access_iterator_tag	iterator_category;
		typedef T							value_type;
		typedef ptrdiff_t					difference_type;
		typedef const T*					pointer;
		typedef const T&					reference;
	};

	//���ص��������
	template <class Iterator>
	inline typename iterator_traits<Iterator>::iterator_category
		iterator_category(const Iterator&) {
		typedef typename iterator_traits<Iterator>::iterator_category category;
		return category();
	}

	//���ر�ʾ���������������
	template <class Iterator>
	inline typename iterator_traits<Iterator>::difference_type* //�������ص��ͱ�
		difference_type(const Iterator&) {
		return < static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
	}

	//���ص�������ָ���������
	template <class Iterator>
	inline typename iterator_traits<Iterator>::value_type*
		value_type(const Iterator&) {
		return < static_cast<typename iterator_traits<Iterator>::value_type*>(0);
	}

	//�����������֧��ģ��������������Ҫ�����е����������ṩ����
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