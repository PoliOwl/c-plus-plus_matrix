#pragma once
#include "linealloc.h"
#include <vector>
#include <ostream>
#include <istream>



template <unsigned N, typename T>
class line {
	linealloc <N, T> alloc;
	T* elem;
	unsigned inplase;
	char delim = ' ';
public:
	line() {
		elem = reinterpret_cast<T*>(alloc.begin);
		inplase = 0;
	}

	line(const T& el) {
		elem = (T*)(alloc.begin);
		inplase = N;
		std::allocator_traits<linealloc<N, T>>::allocate(alloc, N);
		for (size_t i = 0; i < N; ++i) {
			std::allocator_traits<linealloc<N, T>>::construct(alloc, elem + i, el);
		}
	}

	line(const line& other): alloc(std::allocator_traits<linealloc<N,T>>::select_on_container_copy_construction(other.alloc)) {
		elem = (T*)(alloc.begin);
		inplase = other.inplase;
		for (size_t i = 0; i < inplase; ++i) {
			std::allocator_traits<linealloc<N, T>>::construct(alloc, std::allocator_traits<linealloc<N, T>>::allocate(alloc,1), other[i]);
		}
	}

	line(const T* v, size_t n = N) {
		elem = (T*)(alloc.begin);
		(n < N) ? (inplase = n) : (inplase = N);
		std::allocator_traits<linealloc<N, T>>::allocate(alloc, inplase);
		for (size_t i = 0; i < inplase; ++i) {
			std::allocator_traits < linealloc<N, T>>::construct(alloc, elem + i, v[i]);
		}
	}


	line(const std::vector<T>& v): line(v.data(), v.size()) {}

	template <typename...Args>
	void add_back(Args&...arg) {
		if (inplase + 1 <= N) {
			std::allocator_traits<linealloc<N, T>>::construct(alloc, std::allocator_traits<linealloc<N, T>>::allocate(alloc,1), arg...);
			++inplase;
		}
	}

	void add_back(const T& value) {
		if (inplase + 1 <= N) {
			std::allocator_traits<linealloc<N, T>>::construct(alloc, std::allocator_traits<linealloc<N, T>>::allocate(alloc, 1), value);
			++inplase;
		}
	}

	template <typename...Args>
	void replase(std::size_t i, Args&...arg) {
		if (i >= N) {
			throw std::out_of_range("i bigger N");
		}
		if (i < inplase) {
			elem[i] = T(arg...);
		}
		else {
			add_back(arg...);
		}
	}

	void replase(std::size_t i, const T& value) {
		if (i >= N) {
			throw std::out_of_range("i bigger N");
		}
		if (i <= inplase - 1) {
			elem[i] = value;
		}
		else {
			add_back(value);
		}
	}

	~line() {
		for (std::size_t i= 0; i < inplase; ++i) {
			std::allocator_traits<linealloc<N, T>>::destroy(alloc, (T*)(nullptr));
			std::allocator_traits<linealloc<N, T>>::deallocate(alloc, elem, 1);
		}
	}

	T& operator[](std::size_t i) {
		if (i >= N) {
			throw std::out_of_range("out of range");
		}
		return elem[i];

	}

	const T& operator[](std::size_t i) const {
		if (i >= N) {
			throw std::out_of_range("out of range");
		}
		return elem[i];
	}

	bool operator ==(const line<N,T>& operand) {
		if (operand.inplase != (*this).inplase) {
			return false;
		}
		for (size_t i = 0; i < inplase; ++i) {
			if (operand[i] != (*this)[i]) {
				return false;
			}
		}
		return true;
	}

	bool operator !=(const line<N, T>& operand) {
		return !(*this == operand);
	}

	template <unsigned M, typename G>
	bool operator ==(const line<M, G>&) {
		return false;
	}

	template <unsigned M, typename G>
	bool operator !=(const line<M, G>&) {
		return true;
	}

	line<N, T>& operator =(const line<N, T>& operand) {
		for (size_t i= 0; i < operand.inplase; ++i) {
			this->replase(i, operand[i]);
		}
		if (operand.inplase < inplase) {
			for (size_t i = 0; i < inplase - operand.inplase; ++i) {
				std::allocator_traits<linealloc<N, T>>::destroy(alloc, (T*)nullptr);
				std::allocator_traits<linealloc<N, T>>::deallocate(alloc, (T*)nullptr, 1);
			}
		}
		return *this;
	}
	
	line<N, T>& operator *=(const T& operand) {
		for (size_t i = 0; i < N; ++i) {
			elem[i] *= operand;
		}
		return *this;
	}

	line<N, T> operator *(const T& operand) const {
		line<N, T> l = *this;
		return l *= operand;
	}

	line<N, T>& operator+=(const line<N, T>& operand) {
		for (size_t i = 0; i < operand.inplase; ++i) {
			if (i < inplase) {
				(elem[i] += operand[i]);
			} 
			else
			{
				(this->add_back(operand[i]));
			}
		}
		return *this;
	}

	line<N, T> operator +(const line<N, T>& operand) const {
		line<N, T> l = *this;
		return l += operand;
	}

	line<N, T> operator -(const line<N, T>& operand) const {
		line<N, T> l = *this;
		return l -= operand;
	}

	line<N, T> operator-() const {
		line<N, T> l = *this;
		for (size_t i = 0; i < inplase; ++i) {
			l[i] = -l[i];
		}
		return l;
	}

	line<N, T>& operator-=(const line<N, T>& operand) {
		return *this += (-operand);
	}

	line<N, T>& operator*=(const line<N, T>& operand) {
		for (size_t i = 0; i < operand.inplase; ++i) {
			if (i < inplase) {
				elem[i] *= operand[i];
			}
			else
			{
				this->add_back(operand[i]);
			}
		}
		return *this;
	}

	line<N, T> operator*(const line<N, T>& operand) const {
		line<N, T> l = *this;
		return l *= operand;
	}

	T sum() {
		if (inplase) {
			T ans = elem[0];
			for (size_t i = 1; i < inplase; ++i) {
				ans += elem[i];
			}
			return ans;
		}
		throw std::runtime_error("line is empy");
	}

	explicit operator std::vector<T>() {
		std::vector<T> ans(N);
		for (size_t i = 0; i < N; i++) {
			ans[i] = elem[i];
		}
		return ans;
	}

	T* begin() {
		return elem;
	}

	T* end() {
		return elem + N;
	}

	const T* cbegin() const {
		return elem;
	}

	const T* cend() const {
		return elem + N;
	}

	void change_delim(char c) {
		delim = c;
    }

	friend std::ostream& operator <<(std::ostream& os, const line<N, T>& operand) {
		for (size_t i = 0; i < N; ++i) {
			os << operand.elem[i] << operand.delim;
		}
		return os;
	}

	friend std::istream& operator>>(std::istream& is, line<N, T>& operand) {
		for (size_t i = 0; i < N; ++i) {
			T val;
			is >> val;
			operand.replase(i, val);
		}
		return is;
	}

};
