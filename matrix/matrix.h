#pragma once
#include "rational.h"
#include "line.h"

template < typename field, unsigned M, unsigned N = M> class matrix {
protected:
	line<M, line<N, field>> mat;
	//matrix() {};
	template <typename, unsigned , unsigned > friend class matrix;
public:


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
		for (size_t i = 0; i < M; ++i) {
			mat.add_back(line<N, field>((m + (N * i)), N));
		}
	}

	matrix(field m) {
		for (size_t i = 0; i < M; ++i) {
			mat.add_back(line<N, field>(m));
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

	bool operator ==(const matrix<field, M, N>& operand) {
		for (size_t i = 0; i < M; ++i) {
			if (mat[i] != operand.mat[i]) {
				return false;
			}
		}
		return true;
	}

	bool operator != (const matrix<field, M, N>& operand) {
		return !(*this == operand);
	}

	template < typename f, unsigned K, unsigned L = K>
	bool operator == (const matrix<f, K, L>&) {
		return false;
	}

	template < typename f, unsigned K, unsigned L = K>
	bool operator != (const matrix<f, K, L>&) {
		return true;
	}
	
	matrix& operator *=(const field& operand) {
		for (size_t i = 0; i < M; ++i) {
			mat[i] *= operand;
		}
		return *this;
	}

	matrix<field ,M, N> operator -() const {
		matrix<field, M, N> m = *this;
		for (size_t i = 0; i < M; ++i) {
			m[i] = -m[i];
		}
		return m;
	}

	matrix<field, M, N>& operator +=(const matrix<field, M, N>& operand) {
		for (size_t i = 0; i < M; ++i) {
			mat[i] += operand[i];
		}
		return *this;
	}

	matrix<field, M, N>& operator -=(const matrix<field, M, N>& operand) {
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
	
	matrix<field, M, N> operator+(const matrix<field, M, N>& operand) const {
		matrix<M, N, field> m = *this;
		return m += operand;
	}

	matrix<field, M, N> operator-(const matrix<field, M, N>& operand) const {
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

	matrix<field, N, M> transpose() const {
		matrix<field, N, M> ans;
		for (size_t i = 0; i < N; ++i) {
			ans.mat.add_back(this->getColumn(i));
		}
		return ans;
	}


	friend std::ostream& operator<<(std::ostream& os, const matrix<field, M, N>& operand) {
		for (size_t i = 0; i < M; ++i) {
			os << operand.mat[i];
			os << '\n';
		}
		return os;
	}


	template <unsigned K>
	matrix<field, M, K> operator*(const matrix<field, N, K>& operand) const {
		matrix<field, M, K> ans;
		matrix<field, K, N> toperand = operand.transpose();
		for (size_t i = 0; i < M; ++i) {
			ans.mat.add_back(line<K, field>());
			for (size_t j = 0; j < K; ++j) {
				ans.mat[i].add_back((mat[i] * toperand[j]).sum());
			}
		}
		return ans;
	}

	//template <unsigned M, typename f = rational>
	static matrix<field, M> get_ones() {
		matrix<field, M> m(field(0));
		for (size_t i = 0; i < M; ++i) {
			m.mat[i][i] = field(1);
		}
		return m;
	}
	

};



