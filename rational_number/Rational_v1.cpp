#include <cassert>
#include <numeric>
#include <sstream>

#include "Rational_v1.h"

// Class Member Functions
// ======================

// Constructors
Rational::Rational() : Rational{ 0 } {
	std::cout << "\nRunning Rational default constructor...\n";
}
Rational::Rational(int num) : m_numerator{ num }, m_denominator{ 1 } {
	std::cout << "\nRunning Rational(int)/converting constructor...\n";
}
Rational::Rational(int num, int den) : m_numerator{ num }, m_denominator{ den } {
	std::cout << "\nRunning Rational(int, int) constructor...\n";
	reduce();
}

// Assign a (new) numerator and denominator and reduce to normal form.
void Rational::assign(int num, int den) {
	m_numerator = num;
	m_denominator = den;
	reduce();
}

// Reduces the numerator and the denominator to their GCD
// (Greatest Common Denominator)
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

// Unary negation operator: returns the unary negation of rational.
Rational operator-(const Rational& rational) {
	return Rational(-rational.m_numerator, -rational.m_denominator);
}

// I/O Operators
// =============

// Insertion operator: inputs a Rational number, assuming entered content is valid.
// 
// The user is invited to enter the numerator first, and then if that is valid, 
// enter the denominator. If both are valid, they will be used to set the 
// corresponding member variables on rational. If either are invalid, the failbit
// on the input stream is set to indicate input failure.
// 
// The input is initially handled as a string and converted to an integer, as this
// is a more reliable way of doing it than trying to mess around with std::cin 
// inputting an int variable; the user can enter who-knows-what, so it's easier
// to take whatever they input and validate it subsequently.
// 
// The validation is handled by attempting to convert the string to an int using
// std::stoi(). That specifically can throw an invalid argument exception or an
// out of range in the appropriate circumstances. For our purposes here, it's 
// not really important to distinguish, as in the test code we only inform the 
// user there has been an error, based on the state of the input stream,
// and give no specific details of what the issue with the input it.
// 
// Therefore, simply catch an std::exception from stoi; if either exception is 
// thrown, we know the conversion has failed, which is enough to know we need 
// to set the failbit on the ios stream.
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

// Extraction operator: outputs a Rational number as a string in format: 
// numerator/denominator.
std::ostream& operator<<(std::ostream& out, const Rational& rational) {
	std::ostringstream temp{};	
	temp << rational.m_numerator << '/' << rational.m_denominator;
	out << temp.str();

	return out;
}

// Compound Operators
// ==================

// Compound addition operator
Rational& Rational::operator+=(const Rational& rational) {
	m_numerator += rational.m_numerator;
	m_denominator += rational.m_denominator;
	reduce();
	return *this;
}

// Compound subtraction operator
Rational& Rational::operator-=(const Rational& rational) {
	m_numerator -= rational.m_numerator;
	m_denominator -= rational.m_denominator;
	reduce();
	return *this;
}

// Compound multiplication operator
Rational& Rational::operator*=(const Rational& rational) {
	m_numerator *= rational.m_numerator;
	m_denominator *= rational.m_denominator;
	reduce();
	return *this;
}

// Compound division operator
Rational& Rational::operator/=(const Rational& rational) {
	m_numerator /= rational.m_numerator;
	m_denominator /= rational.m_denominator;
	reduce();
	return *this;
}

// Logical Operators
// =================

// Equality operator: returns true if lhs and rhs are equal.
inline bool operator==(const Rational& lhs, const Rational& rhs) {
	return lhs.m_numerator == rhs.m_numerator
		&& lhs.m_denominator == rhs.m_denominator;
}

// Less-than operator: returns true if lhs is less than rhs.
// 
// To compare two rational numbers, the numbers need to be converted
// into a common or comparable form. Mathematically, this means finding 
// the LCM (Least Common Multiple) of the denominators and rewriting 
// them in terms of this LCM.
//
// For example, comparing lhs 2/3 and rhs 5/7:
// The LCM of the denominators 3 and 7 is 21.
// 
// To express lhs 2/3 in terms of 21, multiply its numerator and 
// denominator by 7 (which is rhs's denominator):
// 2 x 7 = 14 | 3 x 7 = 21 | 14/21
//
// To express rhs 5/7 in terms of 21, multiply its numerator and
// denominator by 3 (which is lhs's denominator):
// 5 x 3 = 15 | 7 x 3 = 21 | 15/21
//
// The numerators of these new numbers can be compared:
// 14 < 15 = true
//
// In the code, we skip the calculation of the common denominator itself
// and just calculate the numerators and use that as the basis
// of the logical comparison.
inline bool operator<(const Rational& lhs, const Rational& rhs) {
	return lhs.m_numerator * rhs.m_denominator
		< rhs.m_numerator * lhs.m_denominator;
}

// The rest of the logical comparison operators can be defined
// in terms of the equality and less-than operators.
// The implementations are simpler, but it also means there is no
// need to make them friends, which reduces the number of friend 
// declarations in the class.
bool operator!=(const Rational& lhs, const Rational& rhs) {
	return !(lhs == rhs);
}

bool operator>(const Rational& lhs, const Rational& rhs) {
	return rhs < lhs;
}

bool operator<=(const Rational& lhs, const Rational& rhs) {
	return !(lhs > rhs);
}

bool operator>=(const Rational& lhs, const Rational& rhs) {
	return !(lhs < rhs);
}

// Non-Member Array Functions
// ==========================

// Takes an array of Rational objects and sums up all its constituent
// elements using the += operator. 
// The sum is then divided by the number of elements, giving the arithmetic 
// mean of the elements.
Rational mean(const Rational* collection, int numElements) {
	Rational sum{ 0 };

	for (int i = 0; i < numElements; ++i) {
		const Rational* current = collection + i;
		sum += *current;
	}

	std::cout << "sum is: " << sum << '\n';

	// Mixed type arithmetic - numElements uses Rational's converting constructor.
	return sum /= numElements; // Rational /= int
}

Rational median(const Rational* collection, int numElements) {
	int middleIndex = numElements / 2;

	// Simple case: collection has an odd number of elements, e.g. 5.
	// 5 / 2 = 2.5, which becomes 2 in the integer.
	// Therefore element 2 is the median, so return that.	
	if (numElements % 2 == 1)
		return collection[middleIndex];
	
	// Complex case: the collection has an even number of elements, 
	// e.g. 6 / 2 = 3, so we need to compute the arithmetic mean of the two 
	// middle elements and divide that result by two.
	//
	// Note: uses the converting constructor for the division; i.e. a Rational object
	// is created and stores the result of the two collection elements being added together,
	// and that is divided by the integer literal 2. 
	// 
	// For the actual line of code below, the compiler will produce something like this:
	// 
	//		Rational temp(collection[middleIndex - 1] + collection[middleIndex]);		
	//		return temp / Rational(2);
	//
	// This works because the converting constructor is not marked explicit, so it can be 
	// invoked here. If it were explicit, we would need an additional overload of the division
	// operator that accepted an int as the right operand to ensure this continued to work.
	else
		return (collection[middleIndex - 1] + collection[middleIndex]) / 2;	
}