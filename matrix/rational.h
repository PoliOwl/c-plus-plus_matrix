#pragma once
#include "BigInt.h"

BigInt gcd(BigInt , BigInt);

class rational {
	BigInt top, bottom;
public:
	rational(const BigInt&, const BigInt&);
	rational(const int& a):rational(BigInt(a),1) {};
    rational() {};
	rational& operator+=(const rational&);
	rational operator+(const rational&) const;
	rational& operator-=(const rational&);
	rational operator-(const rational&) const;
	friend std::ostream& operator<<(std::ostream&,const rational&);
	friend std::istream& operator>>(std::istream&, rational&);
	rational operator-() const;
	rational& operator*=(const rational&);
	rational operator*(const rational&) const;
	rational& operator/=(const rational&);
	rational operator/(const rational&) const;
	explicit operator double const() const;
};