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

	T* allocate(size_t n) { //moves pointer forward
		char* here = place + n*(sizeof(T));
		if (here - begin > sizeof(T)* N) { throw std::bad_array_new_length(); }
		place = here;
		return reinterpret_cast<T*>(place-n*sizeof(T));
	}

	void destroy(T* p = nullptr) {//deleting of the last character
		if (p == nullptr) {
			if (!(begin == place)) {
				T* there = reinterpret_cast<T*>(place - sizeof(T));
				there->~T();
			}
		}
		else
		{
			p ->~T();
		}
	}

	void deallocate(T*, size_t n) { //moves pointer
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

	~linealloc() {
		delete begin;
	}
};

