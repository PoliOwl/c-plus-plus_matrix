#include "rational.h"
#define zero BigInt(0)

BigInt gcd(BigInt a, BigInt b) {
	return b ? gcd(b, a % b) : a;
}

std::ostream& operator<<(std::ostream &os, const rational &operand) {
	os << operand.top;
	if (BigInt(1) != operand.bottom) {
		os << "/" << operand.bottom;
	}
	return os;
}

std::istream & operator>>(std::istream &is, rational& operand) {
	BigInt t, b;
	is >> t;
	auto end = [&is](char c) {
		char end[] = { '\n',' ',is.eof(), '/' };
		for (char i : end) {
			if (c == i) {
				return false;
			}
		}
		return true;
	};
	while (!end(is.peek())) {
		is.get();
	}
	is >> b;
	operand = rational(t, b);
	return is;
}

rational::rational(const BigInt& t, const BigInt& b = 1) {
	if (!b) {
		throw 1;
	}
	(t < zero) && (b < zero) ? top = -t, bottom = -b : top = t, bottom = b;
	BigInt div = gcd(abs(top), abs(bottom));
	if (div != BigInt(1)) {
		top /= div;
		bottom /= div;
	}
	if (top >= zero && bottom < zero) {
		top = -top;
		bottom = -bottom;
	}
}

rational& rational::operator+=(const rational &operand) {
	
	if ((top != zero) && (operand.top != zero)) {
		top = top * operand.bottom + operand.top*bottom;
		bottom *= operand.bottom; 
		BigInt div = gcd(abs(top), abs(bottom));
		if (div != BigInt(1)) {
			top /= div;
			bottom /= div;
		}
	}
	else {
		if (top == zero) {
			*this = operand;
		}
	}
	return *this;
}

rational rational::operator+(const rational &operand) const
{
	rational res = *this;
	return res += operand;
}

rational & rational::operator-=(const rational &operand) {
	return *this += (-operand);
}

rational rational::operator-(const rational &operand) const {
	auto res = *this;
	return res -= operand;
}

rational rational::operator-() const {
	return rational(-top, bottom);
}


rational& rational::operator*=(const rational&operand) {
	top *= operand.top;
	bottom *= operand.bottom;
	BigInt div = gcd(abs(top), abs(bottom));
	if (div != BigInt(1)) {
		top /= div;
		bottom /= div;
	}
	return *this;
}

rational rational::operator*(const rational &operand) const {
	rational res = *this;
	return res *= operand;
}

rational& rational::operator/=(const rational &operand) {
	if (!operand.top) {
		throw 2;
	}
	rational div = (operand.top < zero ? rational(-operand.bottom, -operand.top) : rational(operand.bottom, operand.top));
	return *this *= div;
}

rational rational::operator/(const rational &operand) const {
	rational res = *this;
	return res /= operand;
}

bool rational::operator==(const rational& operand) const {
	if (top == operand.top && bottom == operand.bottom) {
		return true;
	}
	else {
		return false;
	}
}

bool rational::operator!=(const rational&operand) const {
	return !(*this == operand);
}

bool rational::operator<(const rational&operand) const {
	if (top * operand.bottom < operand.top * bottom) {
		return true;
	}
	else {
		return false;
	}
}

bool rational::operator>(const rational&operand) const {
	if (top * operand.bottom > operand.top * bottom) {
		return true;
	}
	else {
		return false;
	}
}

bool rational::operator>=(const rational&operand) const {
	return !(*this < operand);
}

bool rational::operator<=(const rational&operand) const {
	return !(*this > operand);
}

rational::operator double const() const {
	double res = static_cast<double>(static_cast<long long>(top)) / static_cast<double>(static_cast<long long>(bottom));
    return res;
}
