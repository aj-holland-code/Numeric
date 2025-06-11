#include <cassert>
#include <numeric>
#include <sstream>

#include "Rational_v2.h"

// Class Member Functions
// ======================

Rational::Rational() : Rational{ 0 } {}
Rational::Rational(int num) : m_numerator{ num }, m_denominator{ 1 } {}
Rational::Rational(int num, int den) : m_numerator{ num }, m_denominator{ den } {
	reduce();
}

// Assign a (new) numerator and denominator and reduce to normal form.
void Rational::assign(int num, int den) {
	m_numerator = num;
	m_denominator = den;
	reduce();
}

// Reduces the numerator and the denominator to their GCD.
void Rational::reduce() {
	assert(m_denominator != 0);

	if (m_denominator < 0) {
		m_denominator = -m_denominator;
		m_numerator = -m_numerator;
	}

	int divisor(std::gcd(m_numerator, m_denominator));
	m_numerator /= divisor;
	m_denominator /= divisor;
}

/*********************************************************************************/
/*********************************************************************************/

// Non-Member Functions
// ====================

// Returns the absolute value of a Rational number.
Rational absolute(const Rational& rational) {
	return Rational(std::abs(rational.m_numerator), rational.m_denominator);
}

// Unary negation operator: returns the unary negation of Rational.
Rational operator-(const Rational& rational) {
	return Rational(-rational.m_numerator, -rational.m_denominator);
}

// I/O Operators
// =============

std::istream& operator>>(std::istream& in, Rational& rational) {
	int numerator = 0;
	int denominator = 0;
	std::string str{};

	std::cout << "Enter a numerator >";
	std::getline(std::cin >> std::ws, str);

	try {
		numerator = std::stoi(str);
	}
	catch ([[maybe_unused]] const std::exception& ex) {
		in.setstate(std::ios::failbit);
	}

	// If the numerator has been successfully entered, proceed to the denominator
	if (std::cin) {
		std::cout << "Enter a denominator (cannot be zero) >";
		std::getline(std::cin >> std::ws, str);
		try {
			denominator = std::stoi(str);
		}
		catch ([[maybe_unused]] const std::exception& ex) {
			in.setstate(std::ios::failbit);
		}
	}

	// If the input has been successful, set it in the Rational object
	if (std::cin)
		rational.assign(numerator, denominator);

	return in;
}

std::ostream& operator<<(std::ostream& out, const Rational& rational) {
	std::ostringstream temp{};
	temp << rational.m_numerator << '/' << rational.m_denominator;
	out << temp.str();

	return out;
}

// Compound Operators
// ==================

Rational& Rational::operator+=(const Rational& rational) {
	m_numerator += rational.m_numerator;
	m_denominator += rational.m_denominator;
	reduce();
	return *this;
}


Rational& Rational::operator-=(const Rational& rational) {
	m_numerator -= rational.m_numerator;
	m_denominator -= rational.m_denominator;
	reduce();
	return *this;
}


Rational& Rational::operator*=(const Rational& rational) {
	m_numerator *= rational.m_numerator;
	m_denominator *= rational.m_denominator;
	reduce();
	return *this;
}


Rational& Rational::operator/=(const Rational& rational) {
	m_numerator /= rational.m_numerator;
	m_denominator /= rational.m_denominator;
	reduce();
	return *this;
}

// Logical Operators
// -----------------
// 
// No need to define logical operators here as the compiler synthesises 
// them, courtesy of the spaceship operator (defined in the header file).

// Less-Than Operator
// ------------------
// 
// However, there is an exception here for the less-than operator: 
// we need more specific behaviour here than the default spaceship operator
// will provide, so this is customised.
// 
// The default version would be based on the equality operator, and thus
// use memberwise comparision, which can yield the wrong result in some
// cases.
//
// For example, 3/4 < 9/14 would evaluate to true using the default
// spaceship operator, but the correct result here is false.
// 
// Therefore we need to define this custom less-than operator to 
// ensure the calculation is done properly.
bool Rational::operator<(const Rational& rhs) {
	return m_numerator * rhs.m_denominator
		< rhs.m_numerator * m_denominator;
}


// Non-Member Array Functions
// ==========================

Rational mean(const Rational* collection, int numElements) {
	Rational sum{ 0 };

	for (int i = 0; i < numElements; ++i) {
		const Rational* current = collection + i;
		sum += *current;
	}

	std::cout << "sum is: " << sum << '\n';
	// Mixed type arithmetic - numElements uses Rational's converting constructor
	return sum /= numElements; // Rational /= int
}

Rational median(const Rational* collection, int numElements) {
	int middleIndex = numElements / 2;

	if (numElements % 2 == 1)
		return collection[middleIndex];
	else
		return (collection[middleIndex - 1] + collection[middleIndex]) / 2;
}