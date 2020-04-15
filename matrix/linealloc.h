#pragma once
template <unsigned N,typename T>
class linealloc {
	char* place;
public:
	
	char*begin;
	typedef T value_type;
	linealloc() {
		place = new char[sizeof(T)*N];
		begin = place;
	}

	T* allocate(size_t n) { //перенос указателя на место после последего элемента 
		char* here = place + n*(sizeof(T));
		if (here - begin > sizeof(T)* N) { throw std::bad_array_new_length(); }
		place = here;
		return (T*)(place-n*sizeof(T));
	}

	void destroy(T* p = nullptr) {//удаление последнего элемента
		if (p == nullptr) {
			if (!(begin == place)) {
				T* there = (T*)(place - sizeof(T));
				there->~T();
			}
		}
		else
		{
			p ->~T();
		}
	}

	void deallocate(T*, size_t n) { //смещениие указателя 
		char* here = place - n * sizeof(T);
		if (here < begin) {
			throw std::exception();
		}
		place = here;
	}

	void select_on_container_copy_construction(const linealloc<N, T>& l) {
		place = new char[sizeof(T) * N];
		begin = place;
	}

	linealloc(const linealloc<N,T>& l) {
		place = new char[sizeof(T)*N];
		begin = place;
	}

	/*linealloc& operator=(const linealloc<N, T>& l) {
		while (place != begin) {
			destroy();
		}
		deallocate();
		place = new char[sizeof(T)*N];
		begin = place;
	}
	*/
	/*template <typename...Args>
	void construct(T* p, Args&...arg) {
		new(p) T(arg...);
	}*/

	~linealloc() {
		delete begin;
	}
};

