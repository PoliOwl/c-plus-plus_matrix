#include <deque>
#include<ostream>
#include<istream>

class BigInt
{
private:
	std::deque<int> num;
	bool sig;
	int compare(const BigInt &bi)const;

public:

	BigInt(long long);
	BigInt(): sig(false) {};
	friend std::ostream& operator<<(std::ostream&, const BigInt&);
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
	operator bool() const;
	explicit operator long long() const;
	BigInt& operator -=(const BigInt&);
	BigInt operator -(const BigInt&) const;
	BigInt& operator /=(const BigInt&);
	BigInt operator /(const BigInt&)const;
	BigInt& operator%=(const BigInt&);
	BigInt operator%(const BigInt&) const;
	BigInt& operator++();
	BigInt operator++(int);
	~BigInt();
	friend BigInt abs(const BigInt&);
};

BigInt abs(const BigInt&);