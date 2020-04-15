#pragma once
#include "rational.h"
#include "line.h"

template <unsigned M, unsigned N, typename field = rational> class matrix {
protected:
	line<M, line<N, field>> mat;
	matrix() {};
	template <unsigned , unsigned , typename > friend class matrix;
public:

	//mattrix() = delete;

	matrix(field** m) {
		for (size_t i = 0; i < M; ++i) {
			mat.add_back(line<N, field>(m[i],N));	
		}
	}

	matrix(line<N, field>* m) {
		for (size_t i = 0; i < M; ++i) {
			mat.add_back(line<N, field>(m[i], N));
		}
	}

	matrix(field* m) {
		//size_t l = 0;
		for (size_t i = 0; i < M; ++i) {
			mat.add_back(line<N, field>(&m[N*i], N));
		}
	}

	matrix(const std::vector<std::vector<field>>& v) {
		for (size_t i = 0; i < M; ++i) {
			mat.add_back(line<N, field>(v[i]));
		}
	};

	matrix(const std::vector<std::vector<int>>& v) {
		for (size_t i = 0; i < M; ++i) {
			mat.add_back(line<N, field>());
			for (size_t j = 0; j < N; ++j) {
				mat[i].add_back(v[i][j]);
			}
		}
	}

	line<N, field>& operator[](size_t i) {
		return mat[i];
	}

	const line<N, field>& operator[](size_t i) const {
		return mat[i];
	}

	bool operator ==(const matrix<M, N, field>& operand) {
		for (size_t i = 0; i < M; ++i) {
			if (mat[i] != operand.mat[i]) {
				return false;
			}
		}
		return true;
	}

	bool operator != (const matrix<M, N, field>& operand) {
		return !(*this == operand);
	}

	template < unsigned K, unsigned L, typename f >
	bool operator == (const matrix<K, L, f>&) {
		return false;
	}

	template < unsigned K, unsigned L, typename f >
	bool operator != (const matrix<K, L, f>&) {
		return true;
	}
	
	matrix& operator *=(const field& operand) {
		for (size_t i = 0; i < M; ++i) {
			mat[i] *= operand;
		}
		return *this;
	}

	matrix<M, N, field> operator -() const {
		matrix<M, N, field> m = *this;
		for (size_t i = 0; i < M; ++i) {
			m[i] = -m[i];
		}
		return m;
	}

	matrix<M, N, field>& operator +=(const matrix<M, N, field>& operand) {
		for (size_t i = 0; i < M; ++i) {
			mat[i] += operand[i];
		}
		return *this;
	}

	matrix<M, N, field>& operator -=(const matrix<M, N, field>& operand) {
		return (*this -= (-operand));
	}


	template<typename G>
	std::enable_if<(std::is_same<G, line<N, field>>::value || std::is_same<G, field*>::value || std::is_same<G, std::vector<field>>::value), 
	void> change_line(size_t i, const G& l) {
		if (i >= M) {
			throw std::out_of_range("matrix does not have this many lines\n");
		}
		mat.replase(i, l);

	}

	
	template<typename G>
	std::enable_if<(std::is_same<G, line<N, field>>::value || std::is_same<G, field*>::value || std::is_same<G, std::vector<field>>::value), 
	void> change_column(size_t i, const G& l) {
		if (i >= N) {
			throw std::out_of_range("matrix does not have this many colummns\n");
		}
		for (size_t j = 0; j < M; ++j) {
			mat[j].replase(i, l[j]);
		}
	}
	
	matrix<M, N, field> operator+(const matrix<M, N, field>& operand) const {
		matrix<M, N, field> m = *this;
		return m += operand;
	}

	matrix<M, N, field> operator-(const matrix<M, N, field>& operand) const {
		matrix<M, N, field> m = *this;
		return m -= operand;
	}
	
	std::vector<field> getRow(size_t i) const{
		return std::vector<field>(mat[i]);
	}

	std::vector<field> getColumn(size_t i) const {
		std::vector<field> ans(M);
		for (size_t j = 0; j < M; j++) {
			ans[j] = mat[j][i];
		}
		return ans;
	}

	matrix<N, M, field> transpose() const {
		matrix<N, M, field> ans;
		for (size_t i = 0; i < N; ++i) {
			ans.mat.add_back(this->getColumn(i));
		}
		return ans;
	}

	friend std::ostream& operator<<(std::ostream& os, const matrix<M, N, field>& operand) {
		for (size_t i = 0; i < M; ++i) {
			os << operand.mat[i];
			os << '\n';
		}
		return os;
	}

	
	template <unsigned K>
	matrix<M, K, field> operator*(const matrix<N, K, field>& operand) const {
	    matrix<M, K, field> ans;
		matrix<K, N, field> toperand = operand.transpose();
		for (size_t i = 0; i < M; ++i) {
			ans.mat.add_back(line<K, field>());
			for (size_t j = 0; j < K; ++j) {
				ans.mat[i].add_back((mat[i] * toperand[j]).sum());
			}
		}
		return ans;
	}

	//friend std::istream& operator>>(std::istream& is, matrix<M, N, field>)
};

template<unsigned N, typename field = rational>
class SquareMatrix : public matrix<N, N, field> {
	/*using matrix::matrix;
	using matrix::operator=;*/

	using matrix<N, N, field>::mat;
public:
	SquareMatrix() {
		matrix<N, N, field>::matrix();
		for (size_t i = 0; i < N; ++i) {
			mat.add_back(line<N, field>(field(0)));
			mat[i][i] = 1;
		}
	}

	
};


/*
class cl {
type *p;
}
main()
{
cl *el = new cl[10];
el[6] = cl(3);
el[6] = cl(5);
}

*/
