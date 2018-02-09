#ifndef _ZT_MEMORY_H_ 
#define _ZT_MEMORY_H_

namespace ztSTL {
	template <typename T>
	class shared_ptr {
	private:
		T* ptr;
		int* ref_num;
	public:
		shared_ptr(T* _ptr=new T()):ptr(_ptr),ref_num(new int(1)){}

	};
}
#endif
