#pragma once
#include <ostream>

template <int N>
class finite {
	unsigned x;
public:
	finite(const int n);
	finite() {
		x = 0;
	}
	finite<N> operator+(const finite<N>&);
	finite<N> operator-(const finite<N>&);
	finite<N> operator*(const finite<N>&);
	finite<N>& operator+=(const finite<N>&);
	finite<N>& operator-=(const finite<N>&);
	finite<N>& operator*=(const finite<N>&);
	finite<N>& operator/=(const finite<N>&);
	finite<N> operator/(const finite<N>&);
	friend std::ostream& operator<<(std::ostream& oc, const finite<N> operand) {
		oc << operand.x << '[' << N << ']';
		return oc;
	}
};

template<int N>
finite<N>::finite(const int n): x(abs(n%N)){
}

template <int N> 
finite<N> finite<N>::operator+(const finite<N>& operand) {
	return finite<N>((x + operand.x) % N);
}

template <int N>
finite<N> finite<N>::operator-(const finite<N>& operand) {
	return finite<N>((x - operand.x) % N);
}

template <int N>
finite<N> finite<N>::operator*(const finite<N>& operand) {
	return finite<N>((x *operand.x) % N);
}

template <int N>
finite<N>& finite<N>::operator+=(const finite<N>& operand) {
	x = (x + operand.x) % N;
	return *this;
}

template <int N>
finite<N>& finite<N>::operator-=(const finite<N>& operand) {
	x = (x - operand.x) % N;
	return *this;
}

template <int N>
finite<N>& finite<N>::operator*=(const finite<N>& operand) {
	x = (x * operand.x) % N;
	return *this;
}

template <int N>
finite<N>& finite<N>::operator/=(const finite<N>& operand) {
	for (int i = 2; i < N / 2; i++) {
		if (N % i == 0) {
			throw std::logic_error("N isn't prime\n");
		}
	}
	x = (x / operand.x) % N;
	return *this;
}

template <int N>
finite<N> finite<N>::operator/(const finite<N>& operand) {
	finite<N> result(x);
	return result /= operand;
}


