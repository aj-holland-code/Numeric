#ifndef RATIONAL_V2_H
#define RATIONAL_V2_H

#include <compare>
#include <iostream>

// Rational Version 2
// ------------------
// 
// As version 1, but uses the C++ three-way/spaceship operator
// (operator<=>) to reduce the number of operator overloads.
class Rational {
public:
	Rational();
	Rational(int num);
	Rational(int num, int den);

	// Defaults are fine for the copy operations & destructor
	Rational(const Rational& r) = default;
	Rational& operator=(const Rational& r) = default;
	~Rational() = default;

	// Other member function
	void assign(int num, int den);

	// Compound operator overloads (member functions)
	Rational& operator+=(const Rational& Rational);
	Rational& operator-=(const Rational& Rational);
	Rational& operator*=(const Rational& Rational);
	Rational& operator/=(const Rational& Rational);

	friend Rational absolute(const Rational& Rational);
	friend Rational operator-(const Rational& Rational);

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
	friend std::ostream& operator<<(std::ostream& out, const Rational& Rational);
	friend std::istream& operator>>(std::istream& in, Rational& Rational);

	// Note that we have a explicit less-than operator, as we want
	// customised behaviour that a default spaceship operator will 
	// not provide.
	bool operator<(const Rational& rhs);

	// C++20 starship operator
	// Ordering: compiler generates the following operators:
	// >
	// <
	// >=
	// <=
	// Default also puts in the == operator
	// Therefore we have all six operators (== also gives !=)
	// Works on memberwise comparison.
	// Returns an std::strong_ordering - int supports strong_ordering by default.
	auto operator<=>(const Rational& rhs) const = default;
private:
	void reduce();
	int m_numerator{};
	int m_denominator{};
};	// End of Rational class

// Prototypes for the non-member array functions
Rational mean(const Rational* collection, int numElements);
Rational median(const Rational* collection, int numElements);

#endif  // RATIONAL_V2_H