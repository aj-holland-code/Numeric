#ifndef RATIONAL_V3_H
#define RATIONAL_V3_H

#include <cassert>
#include <numeric>
#include <sstream>
#include <iostream>
#include <type_traits>

// The concept specifies integral or floating-point types, but excludes
// all char types and unsigned int.
template <typename T>
concept IsNumeric =
!std::same_as<T, char> &&
!std::same_as<T, unsigned char> &&
!std::same_as<T, signed char> &&
!std::is_unsigned_v<T> &&
(std::is_integral_v<T> || std::is_floating_point_v<T>);

template <typename T> requires IsNumeric<T>
class Rational {
public:
	// Constructors
	Rational();
	Rational(T num);
	Rational(T num, T den);

	// Defaults are fine for the copy operations and destructor
	Rational(const Rational& r) = default;
	Rational& operator=(const Rational& r) = default;
	~Rational() = default;

	void assign(int num, int den);

	// Template Class Friends 
	// ----------------------
	// 
	// These are "in situ" friend definitions, as per Dan Saks' advice. 
	// This means the function is defined at the point of declaration.
	// (It could also be defined outside the class and marked inline.)
	//
	// The result is that each instantiation of the Rational class
	// generates its own version of these friend functions.
	// These are non-template functions produced as a side effect of instantiating
	// a template class.

	// Compound Arithmetic Operators (friends)
	// ---------------------------------------
	friend Rational& operator+=(Rational& lhs,
		const Rational& rational) {
		lhs.m_numerator += rational.m_numerator;
		lhs.m_denominator += rational.m_denominator;
		//reduce();
		return lhs;
	}

	friend Rational& operator-=(Rational& lhs,
		const Rational& rational) {
		lhs.m_numerator -= rational.m_numerator;
		lhs.m_denominator -= rational.m_denominator;
		return lhs;
	}

	friend Rational& operator*=(Rational& lhs,
		const Rational& rational) {
		lhs.m_numerator *= rational.m_numerator;
		lhs.m_denominator *= rational.m_denominator;
		return lhs;
	}

	friend Rational& operator/=(Rational& lhs,
		const Rational& rational) {
		lhs.m_numerator /= rational.m_numerator;
		lhs.m_denominator /= rational.m_denominator;
		return lhs;
	}

	// Arithmetic operator overloads (friends)
	// ---------------------------------------

	friend Rational operator+(const Rational& lhs, const Rational& rhs) {
		// Copies lhs, compounds it with rhs, the result of which is
		// reduced, and that result is returned.
		Rational temp(lhs);
		return temp += rhs;
	}

	friend Rational operator-(const Rational& lhs, const Rational& rhs) {
		Rational temp(lhs);
		return temp -= rhs;
	}

	friend Rational operator*(const Rational& lhs, const Rational& rhs) {
		Rational temp(lhs);
		return temp *= rhs;
	}

	friend Rational operator/(const Rational& lhs, const Rational& rhs) {
		Rational temp(lhs);
		return temp /= rhs;
	}

	// Input-Output Operators (friends defined outside class)
	friend std::ostream& operator<<(std::ostream& out, const Rational rational) {
		std::ostringstream temp{};
		temp << rational.m_numerator << '/' << rational.m_denominator;
		out << temp.str();

		return out;
	}

	// Returns the absolute value of a Rational number.
	friend Rational absolute(const Rational& rational) {
		return Rational(std::abs(rational.m_numerator), rational.m_denominator);
	}

	// Unary negation operator: returns the unary negation of rational.
	friend Rational operator-(const Rational& rational) {
		return Rational(-rational.m_numerator, -rational.m_denominator);
	}

	friend std::istream& operator>>(std::istream& in, Rational& rational) {
		T numerator = 0;
		T denominator = 0;
		std::string str{};

		std::cout << "Enter a numerator >";
		std::getline(std::cin >> std::ws, str);

		try {
			if (std::is_same_v<T, double>)
				numerator = std::stod(str);
			else
				numerator = static_cast<T>(std::stoi(str));
		}
		catch ([[maybe_unused]] const std::exception& ex) {
			in.setstate(std::ios::failbit);
		}

		// If the numerator has been successfully entered, proceed to the denominator
		if (std::cin) {
			std::cout << "Enter a denominator (cannot be zero) >";
			std::getline(std::cin >> std::ws, str);
			try {
				if (std::is_same_v<T, double>)
					denominator = std::stod(str);
				else
					denominator = static_cast<T>(std::stoi(str));
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


	// Comparison Operators
	// --------------------

	friend bool operator==(const Rational& lhs, const Rational& rhs) {
		return lhs.m_numerator == rhs.m_numerator
			&& lhs.m_denominator == rhs.m_denominator;
	}

	friend bool operator<(const Rational& lhs, const Rational& rhs) {
		return lhs.m_numerator * rhs.m_denominator
			< rhs.m_numerator * lhs.m_denominator;
	}

	friend bool operator!=(const Rational& lhs, const Rational& rhs) {
		return !(lhs == rhs);
	}

	friend bool operator>(const Rational& lhs, const Rational& rhs) {
		return rhs < lhs;
	}

	friend bool operator<=(const Rational& lhs, const Rational& rhs) {
		return !(lhs > rhs);
	}

	friend bool operator>=(const Rational& lhs, const Rational& rhs) {
		return !(lhs < rhs);
	}

	friend Rational mean(const Rational* collection, int numElements) {
		Rational sum{ 0 };

		for (int i = 0; i < numElements; ++i) {
			const Rational* current = collection + i;
			sum += *current;
		}

		std::cout << "sum is: " << sum << '\n';
		// Mixed type arithmetic - numElements uses Rational's 
		// converting constructor
		return sum /= numElements; // Rational /= int
	}

	friend Rational median(const Rational* collection, int numElements) {
		int middleIndex = numElements / 2;

		if (numElements % 2 == 1)
			return collection[middleIndex];
		else
			return (collection[middleIndex - 1] + collection[middleIndex]) / 2;
	}
private:
	void reduce();
	T m_numerator;
	T m_denominator;
};

// MEMBER FUNCTION DEFINITIONS

// Constructors
template <typename T> requires IsNumeric<T>
Rational<T>::Rational() : Rational{ 0 } {}

template <typename T> requires IsNumeric<T>
Rational<T>::Rational(T num) : Rational{ num, 1 } {}

template <typename T> requires IsNumeric<T>
Rational<T>::Rational(T num, T den)
	: m_numerator{ num }, m_denominator{ den } {
	reduce();
}

// Assign a (new) numerator and denominator and reduce to normal form.
template <typename T> requires IsNumeric<T>
void Rational<T>::assign(int num, int den) {
	m_numerator = num;
	m_denominator = den;
	reduce();
}

// Reduces the numerator and the denominator to their GCD
// (Greatest Common Denominator).
template <typename T> requires IsNumeric<T>
void Rational<T>::reduce() {
	assert(m_denominator != 0);

	if (m_denominator < 0) {
		m_denominator = -m_denominator;
		m_numerator = -m_numerator;
	}

	int divisor(std::gcd(m_numerator, m_denominator));
	m_numerator /= divisor;
	m_denominator /= divisor;
}


#endif  // RATIONAL_V3_H

