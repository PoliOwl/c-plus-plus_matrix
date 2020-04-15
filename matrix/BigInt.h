#include <deque>
#include<ostream>
#include<istream>

class BigInt
{
private:
	std::deque<int> num;
	bool sig;
	int compare(const BigInt &bi)const;
	//BigInt del(BigInt&, const int);
public:
//	BigInt(unsigned *, size_t);
	BigInt(long long);
	BigInt(): sig(false) {};
	friend std::ostream& operator<<(std::ostream&, const BigInt);
	friend std::istream& operator>>(std::istream&, BigInt&);
	BigInt& operator +=(const BigInt&);
	BigInt operator +(const BigInt&) const;
	BigInt operator -() const;
	BigInt& operator *=(const BigInt&);
	BigInt operator*(const BigInt&) const;
	bool operator<(const BigInt&) const;
	bool operator>(const BigInt&) const;
	bool operator==(const BigInt &) const;
	bool operator!=(const BigInt&)const;
	operator bool const() const;
	explicit operator long long const() const;
	BigInt& operator -=(const BigInt&);
	BigInt operator -(const BigInt&) const;
	BigInt& operator /=(const BigInt&);
	BigInt operator /(const BigInt&)const;
	BigInt& operator%=(const BigInt&);
	BigInt operator%(const BigInt) const;
	BigInt& operator++();
	BigInt operator++(int);
	~BigInt();
	friend BigInt abs(const BigInt&);
};

BigInt abs(const BigInt&);