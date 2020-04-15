#include <iostream>
#include "Finite.h"
#include "rational.h"
#include "matrix.h"
#include <vector>



template<typename Container>
void print_iter(const Container& container, const std::string& delimeter = " ", std::ostream& out = std::cout) {
	for (const auto& x : container) {
		out << x << delimeter;
	}
	out << "\n";
}

int main()
{
	const int N = 20, M = 50, K = 30, T = 11;
	finite<T> *r = new finite<T>[M*N];
	for (int i = 1; i <= M * N; ++i) {
		r[i-1] = finite<T>(i);
	}
	matrix<M, N, finite<T>> mn(r);
	//delete r;
	r = new finite<T>[N * K];
	for (int i = 1; i <= N * K; ++i) {
		r[i - 1] = finite<T>(i);
	}
	 matrix<N, K, finite<T>> nk(r);
	//matrix<K, N> kn = nk.transpose();
	//nk.getColumn(mn.mat[])
	std::cout << mn << "\n __________\n" << nk << "\n __________\n";
	std::cout<< mn * nk;
	//std::cout << kn;
}

