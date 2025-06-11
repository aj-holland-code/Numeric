#ifndef RATIONAL_V1_H
#define RATIONAL_V1_H

#include <iostream>

// Rational Version 1
// ------------------
// 
// A rational number is a number that can be expressed as the quotient or
// fraction (p/q) of two integers: a numerator p and a non-zero denominator q.
class Rational {
public:
	// Constructors
	Rational();
	Rational(int num);
	Rational(int num, int den);

	// Defaults are fine for the copy operations and the destructor.
	Rational(const Rational& r) = default;
	Rational& operator=(const Rational& r) = default;	
	~Rational() = default;		
	void assign(int num, int den);
			
	// Compound operator overloads (member functions)
	Rational& operator+=(const Rational& rational);
	Rational& operator-=(const Rational& rational);
	Rational& operator*=(const Rational& rational);
	Rational& operator/=(const Rational& rational);

	friend Rational absolute(const Rational& rational);
	friend Rational operator-(const Rational& rational);

	// Arithmetic operator overloads
	friend Rational operator+(const Rational& lhs, const Rational& rhs) {
		// Copies lhs, compounds it with rhs, the result of which is
		// reduced, and that result is returned.
		return Rational(lhs) += rhs;		
	}

	friend Rational operator-(const Rational& lhs, const Rational& rhs) {
		return Rational(lhs) -= rhs;
	}

	friend Rational operator*(const Rational& lhs, const Rational& rhs) {
		return Rational(lhs) *= rhs;
	}

	friend Rational operator/(const Rational& lhs, const Rational& rhs) {
		return Rational(lhs) /= rhs;
	}

	// Non-member operator overloads
	friend std::ostream& operator<<(std::ostream& out, const Rational& rational);
	friend std::istream& operator>>(std::istream& in, Rational& rational);
	friend bool operator==(const Rational& lhs, const Rational& rhs);
	friend bool operator<(const Rational& lhs, const Rational& rhs);
private:
	void reduce();
	int m_numerator{};
	int m_denominator{};
};	// End of Rational class

// Prototypes for standalone operator overloads - enables other files (in this
// case, the test code file) to find these overloads.
bool operator>(const Rational& lhs, const Rational& rhs);
bool operator<=(const Rational& lhs, const Rational& rhs);
bool operator>=(const Rational& lhs, const Rational& rhs);

// Prototypes for the non-member array functions
Rational mean(const Rational* collection, int numElements);
Rational median(const Rational* collection, int numElements);


#endif  // RATIONAL_V1_H

