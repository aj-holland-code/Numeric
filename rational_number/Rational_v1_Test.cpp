// Rational Numbers
// ----------------
//
// In his CPPCon 2018 presentation "Making New Friends", Dan Saks covers issues with member 
// functions and operator overloads. One of the key ideas presented is how to handle friend 
// functions in class templates, specifically with regard to operator overloads.
// 
// The examples he uses are based around a rational number class, including mean and median
// functions. To illustrate these ideas, the approach I've taken here is to produce three 
// versions of a Rational class:
// 
// - Version 1: non-template, handles integer values only.
// - Version 2: also non-template and int-only, but uses the C++20 three-way operator 
//   (demonstrating how it reduces the amount of code needed for operator overloads).
// - Version 3: template version that allows different precisions for the rational number
//   (demonstrating problems that can be encountered with upgrading a simple
//    non-template class to a template class).
// 
// There are various comments in the header and .cpp files where I felt they were
// appropriate. The idea is to give clear explanations for learning and revision 
// purposes what the code is doing, but hopefully avoid overdoing it.
//
// This file contains a comprehensive set of tests for Rational version 1.

#include <algorithm>
#include <iomanip>
#include <iostream>
#include "Rational_v1.h"

// Test functions
void testConstructors();
void testAssign();
void testCompoundOperators();
void testAbsoluteNegation();
void testArithmeticOperators();
void testIOOperators();
void testEqualityOperators();
void testLessThanOperator();
void testGreaterThanOperator();
void testLessThanOrEqualToOperator();
void testGreaterThanOrEqualToOperator();
void testCalculateMeanAverage();
void testMedian();
void testConst();

int main() {
    testConstructors();   
    testAssign();
    //testCompoundOperators();
    testAbsoluteNegation();
    testArithmeticOperators();
    testIOOperators();
    testEqualityOperators();
    testLessThanOperator();
    testGreaterThanOperator();
    testLessThanOrEqualToOperator();
    testGreaterThanOrEqualToOperator();
    testCalculateMeanAverage();
    testMedian();
    testConst();
}

void testConstructors() {
    std::cout << "Test the  Rational class constructors...\n";

    // No parameters supplied (calls default constructor)
    Rational r1;
    std::cout << "r1: " << r1 << '\n';  // Should print 0/1 (defaults)

    // Supply numerator but not denominator (calls single argument constructor)
    Rational r2(5); 
    std::cout << "r2: " << r2 << '\n'; // Should print 5/1

    // Supply numerator and denominator (calls dual argument constructor)
    Rational r3(12, 24); 
    std::cout << "r3: " << r3 << '\n'; // Should print 1/2 (reduced)

    // Copy constructor (defaulted)
    Rational r4(r2);
    std::cout << "r4: " << r4 << '\n'; // Should print 5/1

    // Copy constructor (defaulted)
    Rational r5 = r3;
    std::cout << "r5: " << r5 << '\n'; // Should print 1/2

    // Copy assignment operator (defaulted)
    r5 = r1;
    std::cout << "r5: " << r5 << '\n'; // Should now print 0/1
}

void testAssign() {
    std::cout << "Test the Rational class assign() function...\n";

    Rational r1(25, 56);
    std::cout << "r1: " << r1 << '\n'; 

    //r1.assign(0, 0); // Should trigger assert as denominator is zero
    r1.assign(10, 11);
    std::cout << "r1: " << r1 << '\n';

    r1.assign(9, 3);
    std::cout << "r1: " << r1 << '\n';

    r1.assign(2, 5.6);  
    std::cout << "r1: " << r1 << '\n';

    r1.assign(-10, -12);
    std::cout << "r1: " << r1 << '\n';

    r1.assign(-4, 7);
    std::cout << "r1: " << r1 << '\n';
}


void testCompoundOperators() {
    std::cout << "Test the Rational class compound arithmetic operators...\n";

    Rational r1(2, 3);
    std::cout << "r1: " << r1 << '\n';

    Rational r2(5, 7);
    std::cout << "r2: " << r2 << '\n';

    // Addition
    std::cout << "\nAdd r2 to r1:\n";
    r1 += r2;
    std::cout << "r1: " << r1 << '\n';
    std::cout << "r2: " << r2 << '\n';

    // Subtraction
    std::cout << "\nSubtract r1 from r2:\n";
    r2 -= r1;
    std::cout << "r1: " << r1 << '\n';
    std::cout << "r2: " << r2 << '\n';

    // Multiplication
    std::cout << "\nMultiply r3 by r4:\n";
    Rational r3(5, 10);
    Rational r4(2, 5);
    std::cout << "r3: " << r3 << '\n';
    std::cout << "r4: " << r4 << '\n';
    
    r3 *= r4;
    std::cout << "r3: " << r3 << '\n';
    std::cout << "r4: " << r4 << '\n';

    // Division
    std::cout << "\nDivide r3 by r4:\n";
    r3 /= r4;
    std::cout << "r3: " << r3 << '\n';
    std::cout << "r4: " << r4 << '\n';

    /*************************************************************************/

    std::cout << "\nTest compound operators with converting constructor...\n";

    Rational r5(10, 15);
    std::cout << "r5: " << r1 << '\n';

    // Addition
    std::cout << "\nAdd 10 to r5:\n";
    r5 += 10;
    std::cout << "r5: " << r5 << '\n';    

    // Subtraction
    std::cout << "\nSubtract 5 from r5:\n";
    r5 -= 5;
    std::cout << "r5: " << r5 << '\n';

    // Multiplication
    std::cout << "\nMultiply r5 by 2:\n";
    r5 *= 2;
    std::cout << "r5: " << r5 << '\n';

    // Division
    std::cout << "\nDivide r5 by 2:\n";
    r5 /= 2;
    std::cout << "r5: " << r5 << '\n';
}

void testAbsoluteNegation() {
    std::cout << "Test Rational absolute() function...\n";

    Rational r1(10, 20);
    std::cout << "r1: " << r1 << '\n';

    Rational r2 = absolute(r1);
    std::cout << "r2: " << r2 << '\n';

    Rational r3(-3, 8);
    std::cout << "r3: " << r3 << '\n';

    Rational r4 = absolute(r3);
    std::cout << "r4: " << r4 << '\n';

    /********************************************************************************/

    std::cout << "\nTest Rational unary negation operator...\n";

    auto r5 = -r1;
    std::cout << "r1: " << r1 << '\n';
    std::cout << "r5: " << r5 << '\n';

    auto r6 = -r3;
    std::cout << "r3: " << r3 << '\n';
    std::cout << "r6: " << r6 << '\n';
}


void testArithmeticOperators() {
    std::cout << "Test the Rational class standard arithmetic operators...\n";

    // Addition
    std::cout << "\nAddition:\n";
    Rational r1(2, 3);
    std::cout << "r1: " << r1 << '\n';

    Rational r2(3, 7);
    std::cout << "r2: " << r2 << '\n';

    // Addition
    std::cout << "r3 = r1 + r2:\n";
    Rational r3 = r1 + r2;
    std::cout << "r1: " << r1 << '\n';
    std::cout << "r2: " << r2 << '\n';
    std::cout << "r3: " << r3 << '\n';

    // Subtraction
    std::cout << "\nSubtraction:\n";
    r1.assign(10, 15);
    r2.assign(20, 35);
    std::cout << "r1: " << r1 << '\n';
    std::cout << "r2: " << r2 << '\n';
    std::cout << "r4 = r2 - r1:\n";
    Rational r4 = r2 - r1;
    std::cout << "r1: " << r1 << '\n';
    std::cout << "r2: " << r2 << '\n';
    std::cout << "r4: " << r4 << '\n';

    // Multiplication
    std::cout << "\nMultiplication:\n";
    r1.assign(5, 10);
    r2.assign(2, 5);
    std::cout << "r1: " << r1 << '\n';
    std::cout << "r2: " << r2 << '\n';
    std::cout << "r5 = r1 * r2:\n";
    Rational r5 = r1 * r2;
    std::cout << "r1: " << r1 << '\n';
    std::cout << "r2: " << r2 << '\n';
    std::cout << "r5: " << r5 << '\n';
    
    // Division
    std::cout << "\nDivision:\n";
    r1.assign(10, 10);
    std::cout << "r1: " << r1 << '\n';
    std::cout << "r2: " << r2 << '\n';
    std::cout << "r6 = r2 / r1:\n";
    Rational r6 = r2 / r1;
    std::cout << "r1: " << r1 << '\n';
    std::cout << "r2: " << r2 << '\n';
    std::cout << "r6: " << r6 << '\n';

    ///*************************************************************************/

    std::cout << "\nTest arithmetic operators with converting constructor...\n";

    Rational r7(10, 15);
    std::cout << "r7 " << r7 << '\n';

    // Addition
    std::cout << "\nr8 = r7 + 10:\n";
    Rational r8 = r7 + 10;
    std::cout << "r7: " << r7 << '\n';
    std::cout << "r8: " << r8 << '\n';

    // Subtraction
    std::cout << "\nr9 = r7 - 5:\n";
    Rational r9 = r7 - 5;
    std::cout << "r7: " << r7 << '\n';
    std::cout << "r9: " << r9 << '\n';

    // Multiplication
    std::cout << "\nr10 = r7 * 2:\n";
    r7.assign(2, 7);
    Rational r10 = r7 * 2;
    std::cout << "r7: " << r7 << '\n';
    std::cout << "r10: " << r10 << '\n';

    // Division
    std::cout << "\nr11 = r10 / 2:\n";
    Rational r11 = r10 / 2;
    std::cout << "r10: " << r10 << '\n';
    std::cout << "r11: " << r11 << '\n';
}

// The output operator has already been tested extensively, so the focus here
// is more on the input operator.
void testIOOperators() {
    std::cout << "Test Rational class I/O operators...\n";

    Rational r1;
    bool invalid = true;
    while (invalid) {
        std::cout << "\nEnter a rational number (integer numerator and denominator)...\n";
        std::cin.clear();
        std::cin >> r1;
        if (std::cin) {
            invalid = false;
            std::cout << "r1: " << r1 << '\n';
        }
        else
            std::cout << "Error on input - try again...\n";
    }
}

void testEqualityOperators() {
    std::cout << "Test Rational class equality operators...\n";

    // Equality
    std::cout << "The equality operator...\n";
    Rational r1(9, 15);
    Rational r2(9, 15);
    std::cout << "r1: " << r1 << '\n';
    std::cout << "r2: " << r2 << '\n';

    // r1 and r2 equal
    if (r1 == r2)
        std::cout << "r1 and r2 are equal\n\n";
    else
        std::cout << "r1 and r2 are not equal (ERROR)\n";

    r2.assign(4, 5);
    std::cout << "r1: " << r1 << '\n';
    std::cout << "r2: " << r2 << '\n';

    // r1 and r2 now different
    if (r1 == r2)
        std::cout << "r1 and r2 are equal (ERROR)\n";
    else
        std::cout << "r1 and r2 are not equal\n";

    /*******************************************************************************/

    // Inequality
    std::cout << "\n\nThe inequality operator...\n";
    r1.assign(9, 15);
    r2.assign(9, 15);
    std::cout << "r1: " << r1 << '\n';
    std::cout << "r2: " << r2 << '\n';

    // r1 and r2 now the same
    if (r1 != r2)
        std::cout << "r1 and r2 are NOT equal (ERROR)\n";
    else
        std::cout << "r1 and r2 are equal\n\n";

    r2.assign(4, 5);
    std::cout << "r1: " << r1 << '\n';
    std::cout << "r2: " << r2 << '\n';

    // r1 and r2 now different
    if (r1 != r2)
        std::cout << "r1 and r2 are NOT equal\n";
    else
        std::cout << "r1 and r2 are equal (ERROR)\n";
}

void testLessThanOperator() {
    std::cout << "Test Rational class less-than operator...\n";

    // Both positive - easy comparison
    std::cout << "Compare two positive rational numbers:\n";
    Rational r1(2, 3);
    Rational r2(5, 7);
    std::cout << "r1: " << r1 << '\n';
    std::cout << "r2: " << r2 << '\n';

    if (r1 < r2)
        std::cout << "r1 is less than r2\n";
    else
        std::cout << "r1 is not less than r1\n";
    if (r2 < r1)
        std::cout << "r2 is less than r1\n";
    else
        std::cout << "r2 is not less than r1\n";

    // Compare positive to negative
    std::cout << "\nCompare positive rational to negative rational number:\n";
    r1.assign(3, 5);
    r2.assign(-2, 3);
    std::cout << "r1: " << r1 << '\n';
    std::cout << "r2: " << r2 << '\n';

    if (r1 < r2)
        std::cout << "r1 is less than r2\n";
    else
        std::cout << "r1 is not less than r1\n";
    if (r2 < r1)
        std::cout << "r2 is less than r1\n";
    else
        std::cout << "r2 is not less than r1\n";

    // Compare negative (denominator) to negative (numerator)
    std::cout << "\nCompare negative denominator to negative numerator:\n";
    r1.assign(3, -4);
    r2.assign(-5, 6);
    std::cout << "r1: " << r1 << '\n';
    std::cout << "r2: " << r2 << '\n';

    if (r1 < r2)
        std::cout << "r1 is less than r2\n";
    else
        std::cout << "r1 is not less than r1\n";
    if (r2 < r1)
        std::cout << "r2 is less than r1\n";
    else
        std::cout << "r2 is not less than r1\n";

    // Compare negative (numerator) to negative (denominator)
    std::cout << "\nCompare negative numerator to negative denominator:\n";
    r1.assign(-4, 9);
    r2.assign(5, -12);
    std::cout << "r1: " << r1 << '\n';
    std::cout << "r2: " << r2 << '\n';

    if (r1 < r2)
        std::cout << "r1 is less than r2\n";
    else
        std::cout << "r1 is not less than r1\n";
    if (r2 < r1)
        std::cout << "r2 is less than r1\n";
    else
        std::cout << "r2 is not less than r1\n";
}

void testGreaterThanOperator() {
    std::cout << "Test Rational class greater-than operator...\n";

    // Both positive - easy comparison
    std::cout << "Compare two positive rational numbers:\n";
    Rational r1(2, 3);
    Rational r2(5, 7);
    std::cout << "r1: " << r1 << '\n';
    std::cout << "r2: " << r2 << '\n';

    if (r1 > r2)
        std::cout << "r1 is greater than r2\n";
    else
        std::cout << "r1 is not greater than r1\n";
    if (r2 > r1)
        std::cout << "r2 is greater than r1\n";
    else
        std::cout << "r2 is not greater than r1\n";

    // Compare positive to negative
    std::cout << "\nCompare positive rational to negative rational number:\n";
    r1.assign(3, 5);
    r2.assign(-2, 3);
    std::cout << "r1: " << r1 << '\n';
    std::cout << "r2: " << r2 << '\n';

    if (r1 > r2)
        std::cout << "r1 is greater than r2\n";
    else
        std::cout << "r1 is not greater than r1\n";
    if (r2 > r1)
        std::cout << "r2 is greater than r1\n";
    else
        std::cout << "r2 is not greater than r1\n";

    // Compare negative (denominator) to negative (numerator)
    std::cout << "\nCompare negative denominator to negative numerator:\n";
    r1.assign(3, -4);
    r2.assign(-5, 6);
    std::cout << "r1: " << r1 << '\n';
    std::cout << "r2: " << r2 << '\n';

    if (r1 > r2)
        std::cout << "r1 is greater than r2\n";
    else
        std::cout << "r1 is not greater than r1\n";
    if (r2 > r1)
        std::cout << "r2 is greater than r1\n";
    else
        std::cout << "r2 is not greater than r1\n";

    // Compare negative (numerator) to negative (denominator)
    std::cout << "\nCompare negative numerator to negative denominator:\n";
    r1.assign(-4, 9);
    r2.assign(5, -12);
    std::cout << "r1: " << r1 << '\n';
    std::cout << "r2: " << r2 << '\n';

    if (r1 > r2)
        std::cout << "r1 is greater than r2\n";
    else
        std::cout << "r1 is not greater than r1\n";
    if (r2 > r1)
        std::cout << "r2 is greater than r1\n";
    else
        std::cout << "r2 is not greater than r1\n";
}

void testLessThanOrEqualToOperator() {
    std::cout << "Test Rational class less-than-or-equal-to operator...\n";

    // Both positive - easy comparison
    std::cout << "Compare two positive rational numbers:\n";
    Rational r1(2, 3);
    Rational r2(5, 7);
    std::cout << "r1: " << r1 << '\n';
    std::cout << "r2: " << r2 << '\n';

    if (r1 <= r2)
        std::cout << "r1 is less than or equal to r2\n";
    else
        std::cout << "r1 is not less than or equal to r1\n";
    if (r2 <= r1)
        std::cout << "r2 is less than or equal to r1\n";
    else
        std::cout << "r2 is not less than or equal to r1\n";

    // Compare positive to negative
    std::cout << "\nCompare positive rational to negative rational number:\n";
    r1.assign(3, 5);
    r2.assign(-2, 3);
    std::cout << "r1: " << r1 << '\n';
    std::cout << "r2: " << r2 << '\n';

    if (r1 <= r2)
        std::cout << "r1 is less than or equal to r2\n";
    else
        std::cout << "r1 is not less than or equal to r1\n";
    if (r2 <= r1)
        std::cout << "r2 is less than or equal to r1\n";
    else
        std::cout << "r2 is not less than or equal to r1\n";

    // Compare negative (denominator) to negative (numerator)
    std::cout << "\nCompare negative denominator to negative numerator:\n";
    r1.assign(3, -4);
    r2.assign(-5, 6);
    std::cout << "r1: " << r1 << '\n';
    std::cout << "r2: " << r2 << '\n';

    if (r1 <= r2)
        std::cout << "r1 is less than or equal to r2\n";
    else
        std::cout << "r1 is not less than or equal to r1\n";
    if (r2 <= r1)
        std::cout << "r2 is less than or equal to r1\n";
    else
        std::cout << "r2 is not less than or equal to r1\n";

    // Compare negative (numerator) to negative (denominator)
    std::cout << "\nCompare negative numerator to negative denominator:\n";
    r1.assign(-4, 9);
    r2.assign(5, -12);
    std::cout << "r1: " << r1 << '\n';
    std::cout << "r2: " << r2 << '\n';

    if (r1 <= r2)
        std::cout << "r1 is less than or equal to r2\n";
    else
        std::cout << "r1 is not less than or equal to r1\n";
    if (r2 <= r1)
        std::cout << "r2 is less than or equal to r1\n";
    else
        std::cout << "r2 is not less than or equal to r1\n";
}

void testGreaterThanOrEqualToOperator() {
    std::cout << "Test Rational class greater-than-or-equal-to operator...\n";

    // Both positive - easy comparison
    std::cout << "Compare two positive rational numbers:\n";
    Rational r1(2, 3);
    Rational r2(5, 7);
    std::cout << "r1: " << r1 << '\n';
    std::cout << "r2: " << r2 << '\n';

    if (r1 >= r2)
        std::cout << "r1 is greater than or equal to r2\n";
    else
        std::cout << "r1 is not greater than or equal to r1\n";
    if (r2 >= r1)
        std::cout << "r2 is greater than or equal to r1\n";
    else
        std::cout << "r2 is not greater than or equal to r1\n";

    // Compare positive to negative
    std::cout << "\nCompare positive rational to negative rational number:\n";
    r1.assign(3, 5);
    r2.assign(-2, 3);
    std::cout << "r1: " << r1 << '\n';
    std::cout << "r2: " << r2 << '\n';

    if (r1 >= r2)
        std::cout << "r1 is greater than or equal to r2\n";
    else
        std::cout << "r1 is not greater than or equal to r1\n";
    if (r2 >= r1)
        std::cout << "r2 is greater than or equal to r1\n";
    else
        std::cout << "r2 is not greater than or equal to r1\n";

    // Compare negative (denominator) to negative (numerator)
    std::cout << "\nCompare negative denominator to negative numerator:\n";
    r1.assign(3, -4);
    r2.assign(-5, 6);
    std::cout << "r1: " << r1 << '\n';
    std::cout << "r2: " << r2 << '\n';

    if (r1 >= r2)
        std::cout << "r1 is greater than or equal to r2\n";
    else
        std::cout << "r1 is not greater than or equal to r1\n";
    if (r2 >= r1)
        std::cout << "r2 is greater than or equal to r1\n";
    else
        std::cout << "r2 is not greater than or equal to r1\n";

    // Compare negative (numerator) to negative (denominator)
    std::cout << "\nCompare negative numerator to negative denominator:\n";
    r1.assign(-4, 9);
    r2.assign(5, -12);
    std::cout << "r1: " << r1 << '\n';
    std::cout << "r2: " << r2 << '\n';

    if (r1 >= r2)
        std::cout << "r1 is greater than or equal to r2\n";
    else
        std::cout << "r1 is not greater than or equal to r1\n";
    if (r2 >= r1)
        std::cout << "r2 is greater than or equal to r1\n";
    else
        std::cout << "r2 is not greater than or equal to r1\n";
}


void testCalculateMeanAverage() {
    std::cout << "Test Rational class mean() function (calculates mean average of collection of Rational objects)...\n";

    Rational collection[] = { Rational(2, 7), Rational(2, 5), Rational(10, 11), 
                              Rational(4, 12), Rational(4, 8), Rational(10, 12)};
    int numElements = std::size(collection);

    // Iterate through collection first
    std::cout << "There are " << numElements << " Rational numbers in the collection.\n";
    std::cout << "The contents of the collection:\n\n";
   
    for (int i = 0; i < std::size(collection); ++i) {
        Rational* current = collection + i;
        std::cout << "Element " << i << ": " << *current << '\n';
    }

    Rational result = mean(collection, numElements);
    std::cout << "\nThe mean average of the collection is: " << result << '\n';
}

void testMedian() {
    std::cout << "Test Rational class median() function (returns middle element of a sorted collection of Rational objects)...\n";

    // Array 1 - odd number of elements
    std::cout << "The first array has five elements (odd number), so the median element will be the one "
        << " in position 2 (after sorting)...\n";
    
    Rational collection[] = { Rational(2, 7), Rational(2, 5), Rational(10, 11),
                              Rational(4, 12), Rational(4, 8) };

    int numElements = std::size(collection);
    std::cout << "There are " << numElements << " Rational numbers in the collection.\n";

    std::cout << "\nThe contents of the collection before sorting:\n\n";

    for (int i = 0; i < std::size(collection); ++i) {
        Rational* current = collection + i;
        std::cout << "Element " << i << ": " << *current << '\n';
    }

    // Sort the collection
    std::sort(collection, collection + numElements);

    // Iterate through collection first
    std::cout << "\nThe contents of the collection after sorting:\n\n";   
    for (int i = 0; i < std::size(collection); ++i) {
        Rational* current = collection + i;
        std::cout << "Element " << i << ": " << *current << '\n';
    }

    Rational middle = median(collection, numElements);
    std::cout << "\nThe median element of the collection: " << middle << '\n';

    // There should be no risk of modifying the contents, but check anyway
    std::cout << "\nThe contents of the collection after calculating the median:\n\n";
    for (int i = 0; i < std::size(collection); ++i) {
        Rational* current = collection + i;
        std::cout << "Element " << i << ": " << *current << '\n';
    }

    /*******************************************************************************/

    // Array 2 - an even number of elements
    std::cout << "\n\nThe first array has six elements (even number), so the median element "
        << "will be the sum of the elements in positions 2 and 3 (after sorting) divided by 2...\n";
    
    Rational collection2[] = { Rational(12, 13), Rational(3, 5), Rational(10, 18),
                              Rational(4, 12), Rational(4, 50), Rational(5, 6)};

    int numElements2 = std::size(collection2);
    std::cout << "There are " << numElements2 << " Rational numbers in the collection.\n";

    std::cout << "\nThe contents of the second collection before sorting:\n\n";

    for (int i = 0; i < std::size(collection2); ++i) {
        Rational* current = collection2 + i;
        std::cout << "Element " << i << ": " << *current << '\n';
    }

    // Sort the collection
    std::sort(collection2, collection2 + numElements2);

    // Iterate through collection first
    std::cout << "\nThe contents of the second collection after sorting:\n\n";
    for (int i = 0; i < std::size(collection2); ++i) {
        Rational* current = collection2 + i;
        std::cout << "Element " << i << ": " << *current << '\n';
    }

    Rational middle2 = median(collection2, numElements2);
    std::cout << "\nThe median element of the second collection: " << middle2 << '\n';

    // Check no elements have been modified
    std::cout << "\nThe contents of the second collection after calculating the median:\n\n";
    for (int i = 0; i < std::size(collection2); ++i) {
        Rational* current = collection2 + i;
        std::cout << "Element " << i << ": " << *current << '\n';
    }
}


void testConst() {
    std::cout << "\nTest a const version of a Rational number...\n";

    const Rational r1(8, 12);
    const Rational r2(r1);

    // Output operator should work
    std::cout << "r1: " << r1 << '\n';   
    std::cout << "r2: " << r2 << '\n';

    // Arithmetic operators return a new instance so should work
    const Rational r3 = r1 + r2;
    std::cout << "r3: " << r3 << '\n';

    const Rational r4 = r3 - 1;
    std::cout << "r4: " << r4 << '\n';

    const Rational r5 = r1 * r2;
    std::cout << "r5: " << r5 << '\n';

    const Rational r6 = r1 / r2;
    std::cout << "r6: " << r6 << "\n\n";

    // Logical comparison operators should work
    std::cout << std::boolalpha;
    std::cout << "r1 and r2 are equal:               " << (r1 == r2) << '\n';
    std::cout << "r1 and r2 are NOT equal:           " << (r1 != r2) << '\n';
    std::cout << "r1 is less than r2:                " << (r1 < r2) << '\n';
    std::cout << "r1 is less than or equal to r2:    " << (r1 <= r2) << '\n';
    std::cout << "r1 is greater than r2:             " << (r1 > r2) << '\n';
    std::cout << "r1 is greater than or equal to r2: " << (r1 >= r2) << '\n';

    // mean() and median() should work; however, they use const Rational 
    // parameters and have been tested earlier with non-const arguments; 
    // testing them here with const arguments adds nothing new, so these
    // tests are omitted.

    // Calling any functions or operators that mutate the object should result in an error.
    std::cout << "\n\n";
    //r1.assign(4, 5);
    //r1 += r2;
    //r1 -= r2;
    //r1 *= r2;
    //r1 /= r2;
 }