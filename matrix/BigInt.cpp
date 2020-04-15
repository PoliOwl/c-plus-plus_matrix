#include "BigInt.h"


BigInt::BigInt(long long number) :sig(number<0)
{
	//sig = number>0;
	if (!number) {
		num.push_back(0);
		return;
	}
	number = llabs(number);
	for (; number; number /= 10)
	{
		num.push_back(number % 10);
	
	}
}

BigInt& BigInt::operator+=(const BigInt  &  b) {
	int ten = 0;
	for (; num.size() < b.num.size(); num.push_back(0));
	auto f = false;
	//auto min = [](size_t a, size_t b) {return a < b ? a : b; };
	if ((sig&&b.sig) || (!sig && !b.sig)) {
		for (int i = 0; i < b.num.size() || ten; ++i) {

			num[i] += ten + (i<b.num.size() ? b.num[i] : 0 );
			ten = num[i] / 10;
			num[i] = num[i] % 10;
			if (ten&& i+1 == num.size()) {
				num.push_back(0);
			}
		}
	}
	else {
		int j = b.num.size() - 1;
		if (num[j] < b.num[j]) {
			(sig = !sig);
		}
		int left = 0;
		bool bigger = abs(*this)>abs(b);
		//for (bigger = (num[j] > b.num[j]) || (num.size() > b.num.size()); j > 0 && (num[j] == b.num[j]) && (num.size() == b.num.size()); --j, bigger = (num[j] > b.num[j]));
		for (int i = 0; i < b.num.size(); ++i) {
			if (bigger) {
				int g;
				for (g = i + 1;g!=num.size()&&num[g] == 0; ++g);
				left = ((num[i] - b.num[i]) < 0);
				if (i + 1 != num.size()) {
					num[g] -= 1 * left;
				}
				num[i] = 10 * left + num[i] - b.num[i];
			}
			else {
				int minus = b.num[i] - ten * (b.num[i] != 0);
				left = ((minus - num[i]) < 0);
				num[i] = 10 * left + minus - num[i];
				(i + 1 < j + 1 && b.num[i + 1] != 0) ? (ten = 1 * left) : (ten += 1 * left);
			}
		}
		for (; num[num.size()-1] == 0&&num.size()>1; num.pop_back());
	}
	return *this;
}

BigInt BigInt::operator+(const BigInt& operand) const {
	BigInt sum = *this;
	return sum += operand;
}

BigInt BigInt::operator-() const{
	BigInt b = *this;
	b.sig = !sig;
	return b;
}

BigInt & BigInt::operator*=(const BigInt & operand)
{
	BigInt res = 0;
	size_t ten1 = 1, ten2 = 1;
	for (size_t i = 0; i < num.size(); i++) {
		ten2 = 1;
		for (size_t j = 0; j < operand.num.size(); j++) {
			res += ten1 * num[i] * ten2*operand.num[j];
			ten2 *= 10;
		}
		ten1 *= 10;
	}
	res.sig = !((sig&&operand.sig) || (!sig && !operand.sig));
	*this = res;
	return *this;
}

BigInt BigInt::operator*(const BigInt &operand)const {
	BigInt res = *this;
	res *= operand;
	return res;
}

bool BigInt::operator<(const BigInt &bi)const {
	return(this->compare(bi) == 1);
	
}


int BigInt::compare(const BigInt &bi) const { // -1 - they equal, 0 - this bigger, 1 - this smaller
	if (this->num.size() > bi.num.size()) {
		return this->sig;
	}
	else {
		if (this->num.size() < bi.num.size()) {
			return !((this->sig) || (bi.sig));
		}
		else {
			for (size_t i = this->num.size(); i >0; --i) {
				size_t j = i - 1;
				if (this->num[j] > bi.num[j]) {
					return this->sig;
				}
				else if (this->num[j] < bi.num[j]) {
					return !((this->sig) && (bi.sig));
				}
			}
			return -1;
		}
	}
}

//BigInt BigInt::del(BigInt &operand, const int devide) {
//	BigInt ten = 0;
//	for (int i = operand.num.size(); i > -1; --i) {
//		long long ans = operand.num[i] + (ten *= 10);
//		operand.num[i] = int(ans / devide);
//		ten = int(ans%devide);
//	}
//	return ten;
//}

bool BigInt::operator>(const BigInt &bi)const {
	 return (this->compare(bi) == 0) ;
	
}

bool BigInt::operator==(const BigInt &bi)const {
	return (this->compare(bi) == -1);
}

bool BigInt::operator!=(const BigInt &operand) const
{
	return !(*this==operand);
}

BigInt::operator bool const()const {
	return(num[num.size() - 1]);
}

BigInt::operator long long const() const {
	long long res = num[num.size()-1];
	for (int i = num.size() - 2; i >= 0; --i) {
		res *= 10;
		res += num[i];
	}
	if (sig) {
		res = -res;
	}
	return res;
}

BigInt abs(const BigInt &operand) {
	BigInt res = operand;
	res.sig = false;
	return res;
}

BigInt& BigInt::operator-=(const BigInt &operand) {
	*this += (-operand);
	return *this;
}

BigInt BigInt::operator-(const BigInt &operand) const {
	auto sum = *this;
	return (sum -= operand);
}

BigInt& BigInt::operator/=(const BigInt &operand)
{
	if (!operand) { throw std::logic_error("division by zero"); }
	if (abs(operand) > abs(*this)) {
		*this = 0;
		return *this;
	}
	BigInt devided = 0;
	BigInt absoperand = abs(operand);
	
	for (int i = num.size(); (devided < absoperand); --i, devided *=10,devided += num[i]);
	BigInt ans =0;
	for (int i = num.size() - devided.num.size() - 1; i > -2; --i) {
		int letter;
		BigInt check;
		for (letter = 1; BigInt(letter)*absoperand < devided; ++letter);
		check = BigInt(letter)*absoperand;
		ans *= 10;
		ans += letter-1*(check!=devided);
		devided -= (BigInt(ans.num[0])*absoperand);
		if (i > -1) {
			devided *= 10;
			devided += num[i];
		}
	}
	auto s = this->sig;
	*this = ans;
	s == operand.sig ? sig = false : sig = true;
	return *this;

}

BigInt BigInt::operator/(const BigInt &operand) const {
	BigInt res = *this;
	return res /= operand;
}

BigInt & BigInt::operator%=(const BigInt &operand)
{
	if (!operand) { throw std::logic_error("division by zero"); }
	if (abs(operand) > abs(*this)) {
		return *this;
	}
	BigInt devided = 0;
	BigInt absoperand = abs(operand);
	
	for (int i = num.size(); (devided < absoperand); --i, devided *= 10, devided += num[i]);
	BigInt ans = 0;
	for (int i = num.size() - devided.num.size() - 1; i > -2; --i) {
		int letter;
		BigInt check;
		for (letter = 1; BigInt(letter)*absoperand < devided; ++letter);
		check = BigInt(letter)*absoperand;
		ans *= 10;
		ans += letter - 1 * (check != devided);
		devided -= (BigInt(ans.num[0])*absoperand);
		if (i > -1) {
			devided *= 10;
			devided += num[i];
		}
		
	}
	auto s=this->sig;
	*this = devided;
	s == operand.sig ? sig = false : sig = true;
	return *this;
}

BigInt BigInt::operator%(const BigInt operand) const {
	BigInt res = *this;
	return res %= operand;
}

BigInt & BigInt::operator++() {
	return *this += 1;
}

BigInt BigInt::operator++(int) {
	BigInt res = *this;
	*this += 1;
	return res;
}

BigInt::~BigInt() {
}

 std::ostream & operator<<(std::ostream& str, const BigInt bi) {
	if (bi.sig) {
		str << '-';
	}
	for (size_t i = bi.num.size()-1; i >0; --i)
	{
		str << bi.num[i];
	}
	str << bi.num[0];
	return str;
 }

 std::istream & operator>>(std::istream& str, BigInt& bi) {
	 char c;
	// size_t i = 0;
	 bi = BigInt();

	 str >> c;

	 if (!(bi.sig = (c == 45)))
	 {
		 if ((c >= '0') && (c <= '9' ))
		 {
			 bi.num.push_back(c - '0');
			// ++i;
		 }
		 else
		 {
			 if (c == '+') {
				 (bi.sig = false);
			 }

		 }
	 }
	 auto end = [&str](char c){
		 char end[] = { '\n',' ',str.eof(), '/' };
		 for (char i : end) {
			 if (c == i) {
				 return false;
			 }
		 }
		 return true;
	 };
	while ( end(str.peek()))
	 {
		c = str.get();
		if ((c >= '0') && (c <= '9'))
		{
			bi.num.push_front(c - '0');
			//++i;
		}
		else
		{
			bi = BigInt(0);
		}
	 }
	return str;
 }
