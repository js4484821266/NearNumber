#pragma once
#include<cstdint>
#include<vector>
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define SGN(x) ((x)<0?intmax_t(-1):intmax_t(1))
#define ABS(x) ((x)*SGN(x))
class BigInteger {
	bool s = 0;

	typedef  uint8_t digitt;

	typedef std::vector<digitt> mantissat;

	mantissat m;

	void fit(void) {
		while (m.size() > 1)
			if (!m.back())
				m.pop_back();
			else
				break;
	}

public:

	intmax_t sgn(void) const {
		return 1 - 2 * (intmax_t)s;
	}

	bool boolsgn(void)const {
		return s;
	}

	const mantissat& mantissa(void)const {
		return m;
	}

	size_t size(void)const {
		return m.size();
	}

	const BigInteger& operator=(const BigInteger& x) {
		s = x.boolsgn();
		m = x.mantissa();
		return x;
	}

	/* "ExEZ" means "there exists x, an integer." */
	template<typename ExEZ>
	const ExEZ& operator=(const ExEZ& x) {
		s = (x < 0);
		m.clear();
		for (
			size_t t = 0;
			t < sizeof(ExEZ) / sizeof(digitt);
			t++
			)
			m.push_back(
				digitt(
					ABS(x) >> (sizeof(digitt) * 8 * t)
				)
			);
		fit();
		return x;
	}

	BigInteger(void) {
		operator=(0);
	}

	BigInteger(const BigInteger& x) {
		operator=(x);
	}

	/* "ExEZ" means "there exists x, an integer." */
	template<typename ExEZ>
	BigInteger(const ExEZ& x) {
		operator=(x);
	}

	operator bool() const {
		for (
			size_t t = 0;
			t < m.size();
			t++
			)
			if (m[t])
				return true;
		return false;
	}

	/* "ExEZ" means "there exists x, an integer." */
	template<typename ExEZ>
	operator ExEZ()const {
		ExEZ x = 0;
		for (
			size_t t = 0;
			t < MIN(m.size() * sizeof(digitt), sizeof(ExEZ)) / sizeof(digitt);
			t++
			)
			x |= (ExEZ(m[t]) << (sizeof(digitt) * 8 * t));
		return x * sgn();
	}

	bool operator!() const {
		return !operator bool();
	}

	bool operator&&(const BigInteger x)const {
		return operator bool() && (bool)x;
	}

	/* "Ax" means "for all x." */
	template<typename Ax>
	bool operator&&(const Ax x) const {
		return operator bool() && x;
	}

	bool operator||(const BigInteger x) const {
		return operator bool() || (bool)x;
	}

	/* "Ax" means "for all x." */
	template<typename Ax>
	bool operator||(const Ax x)const {
		return operator bool() || x;
	}

	bool operator==(const BigInteger x)const {
		return s == x.boolsgn() && m == x.mantissa();
	}

	bool operator!=(const BigInteger x)const {
		return!operator==(x);
	}

	bool operator>(const BigInteger x)const {
		if (s != x.boolsgn())
			return x.boolsgn();
		else
			if (size() != x.size())
				return (size() > x.size()) != s;
			else {
				size_t t = size();
				while (t) {
					--t;
					if (m[t] > x.mantissa()[t])
						return!s;
				}
				return s;
			}
	}

	bool operator<(const BigInteger x)const{
		return !operator>(x) && !operator==(x);
	}

	bool operator>=(const BigInteger x)const {
		return!operator<(x);
	}

	bool operator<=(const BigInteger x)const {
		return !operator>(x);
	}

	BigInteger operator<<(const BigInteger x)const;

	BigInteger operator>>(const BigInteger x)const;

	BigInteger operator+(const BigInteger x)const;

	BigInteger operator-(const BigInteger x)const;

	BigInteger operator*(const BigInteger x)const;

	BigInteger operator/(const BigInteger x)const;

	BigInteger operator%(const BigInteger x)const;

	BigInteger operator-()const;
};
typedef BigInteger __intn;