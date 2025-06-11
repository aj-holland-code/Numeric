// Rational Version 3
// ------------------
// 
// This file is for tests of the template version of the Rational class.
// It is running the same tests as those for the first version, but
// using long as the template type parameter.

#include <algorithm>
#include <iostream>
#include "Rational_v3.h"

void testDeletedTypes();

// Long tests
void testLongConstructors();
void testLongAssign();
void testLongCompoundOperators();
void testLongAbsoluteNegation();
void testLongArithmeticOperators();
void testLongIOOperators();
void testLongEqualityOperators();
void testLongLessThanOperator();
void testLongGreaterThanOperator();
void testLongLessThanOrEqualToOperator();
void testLongGreaterThanOrEqualToOperator();
void testLongCalculateMeanAverage();
void testLongMedian();

int main() {
    testDeletedTypes();

    // Long tests
    testLongConstructors();
    testLongAssign();
    testLongCompoundOperators();
    testLongAbsoluteNegation();
    testLongArithmeticOperators();
    testLongIOOperators();
    testLongEqualityOperators();
    testLongLessThanOperator();
    testLongGreaterThanOperator();
    testLongLessThanOrEqualToOperator();
    testLongGreaterThanOrEqualToOperator();
    testLongCalculateMeanAverage();
    testLongMedian();
}

void testDeletedTypes() {
    std::cout << "Test that the types of Rational we want to prevent from being instantiated cannot be instantiated...\n";

    // Sanity check legitimate types that *can* be instantiated
    Rational<short> tr_short(10, 15);
    Rational<intmax_t> tr_intmax(4, 6);

    // The code will not compile if any of the following lines are active
    // Instantiation of a Rational for any of these types is prevented
    // the the use of a concept.

    class MyClass {
    public:
        int num{};
    };

    //Rational<MyClass> tr_mc(4, 6);   
    //Rational<char> tr_char('1','5');
    //Rational<unsigned char> tr_uschar('f', 'g');
    //Rational<std::string> tr_string("10", "15");   
    //Rational<unsigned> tr_unsigned(5, 7);
}

/************************ TESTS FOR LONG TYPE ***********************************/

void testLongConstructors() {
    std::cout << "Test the Rational<long> class constructors...\n";

    // No parameters supplied (calls default constructor)
    Rational<long> r1;
    std::cout << "r1: " << r1 << '\n';  // Should print 0/1 (defaults)

    // Supply numerator but not denominator (calls single argument constructor)
    Rational<long> r2(5);
    std::cout << "r2: " << r2 << '\n'; // Should print 5/1

    // Supply numerator and denominator (calls dual argument constructor)
    Rational<long> r3(12, 24);
    std::cout << "r3: " << r3 << '\n'; // Should print 1/2 (reduced)

    // Copy constructor (defaulted)
    Rational<long> r4(r2);
    std::cout << "r4: " << r4 << '\n'; // Should print 5/1

    // Copy constructor (defaulted)
    Rational<long> r5 = r3;
    std::cout << "r5: " << r5 << '\n'; // Should print 1/2

    // Copy assignment operator (defaulted)
    r5 = r1;
    std::cout << "r5: " << r5 << '\n'; // Should now print 0/1
}

void testLongAssign() {
    std::cout << "Test the Rational<long> class assign() function...\n";

    Rational<long> r1(25, 56);
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

void testLongCompoundOperators() {
    std::cout << "Test the Rational<long> class compound arithmetic operators...\n";

    Rational<long> r1(2, 3);
    std::cout << "r1: " << r1 << '\n';

    Rational<long> r2(5, 7);
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
    Rational<long> r3(5, 10);
    Rational<long> r4(2, 5);
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

    Rational<long> r5(10, 15);
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

void testLongAbsoluteNegation() {
    std::cout << "Test Rational<long> absolute() function...\n";

    Rational<long> r1(10, 20);
    std::cout << "r1: " << r1 << '\n';

    Rational<long> r2 = absolute(r1);
    std::cout << "r2: " << r2 << '\n';

    Rational<long> r3(-3, 8);
    std::cout << "r3: " << r3 << '\n';

    Rational<long> r4 = absolute(r3);
    std::cout << "r4: " << r4 << '\n';

    /********************************************************************************/

    std::cout << "\n\nTest Rational<long> unary negation operator...\n";

    auto r5 = -r1;
    std::cout << "r1: " << r1 << '\n';
    std::cout << "r5: " << r5 << '\n';

    auto r6 = -r3;
    std::cout << "r3: " << r3 << '\n';
    std::cout << "r6: " << r6 << '\n';
}

void testLongArithmeticOperators() {
    std::cout << "Test the Rational<long> class standard arithmetic operators...\n";

    // Addition
    std::cout << "\nAddition:\n";
    Rational<long> r1(2, 3);
    std::cout << "r1: " << r1 << '\n';

    Rational<long> r2(3, 7);
    std::cout << "r2: " << r2 << '\n';

    // Addition
    std::cout << "r3 = r1 + r2:\n";
    Rational<long> r3 = r1 + r2;
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
    Rational<long> r4 = r2 - r1;
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
    Rational<long> r5 = r1 * r2;
    std::cout << "r1: " << r1 << '\n';
    std::cout << "r2: " << r2 << '\n';
    std::cout << "r5: " << r5 << '\n';

    // Division
    std::cout << "\nDivision:\n";
    r1.assign(10, 10);
    std::cout << "r1: " << r1 << '\n';
    std::cout << "r2: " << r2 << '\n';
    std::cout << "r6 = r2 / r1:\n";
    Rational<long> r6 = r2 / r1;
    std::cout << "r1: " << r1 << '\n';
    std::cout << "r2: " << r2 << '\n';
    std::cout << "r6: " << r6 << '\n';

    ///*************************************************************************/

    std::cout << "\nTest arithmetic operators with converting constructor...\n";

    Rational<long> r7(10, 15);
    std::cout << "r7 " << r7 << '\n';

    // Addition
    std::cout << "\nr8 = r7 + 10:\n";
    Rational<long> r8 = r7 + 10;
    std::cout << "r7: " << r7 << '\n';
    std::cout << "r8: " << r8 << '\n';

    // Subtraction
    std::cout << "\nr9 = r7 - 5:\n";
    Rational<long> r9 = r7 - 5;
    std::cout << "r7: " << r7 << '\n';
    std::cout << "r9: " << r9 << '\n';

    // Multiplication
    std::cout << "\nr10 = r7 * 2:\n";
    r7.assign(2, 7);
    Rational<long> r10 = r7 * 2;
    std::cout << "r7: " << r7 << '\n';
    std::cout << "r10: " << r10 << '\n';

    // Division
    std::cout << "\nr11 = r10 / 2:\n";
    Rational<long> r11 = r10 / 2;
    std::cout << "r10: " << r10 << '\n';
    std::cout << "r11: " << r11 << '\n';
}

void testLongIOOperators() {
    std::cout << "Test Rational<long> class I/O operators...\n";

    Rational<long> r1;
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

void testLongEqualityOperators() {
    std::cout << "Test Rational<long> class equality operators...\n";

    // Equality
    std::cout << "The equality operator...\n";
    Rational<long> r1(9, 15);
    Rational<long> r2(9, 15);
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


void testLongLessThanOperator() {
    std::cout << "Test Rational<long> class less-than operator...\n";

    // Both positive - easy comparison
    std::cout << "Compare two positive rational numbers:\n";
    Rational<long> r1(2, 3);
    Rational<long> r2(5, 7);
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

void testLongGreaterThanOperator() {
    std::cout << "Test Rational<long> class greater-than operator...\n";

    // Both positive - easy comparison
    std::cout << "Compare two positive rational numbers:\n";
    Rational<long> r1(2, 3);
    Rational<long> r2(5, 7);
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


void testLongLessThanOrEqualToOperator() {
    std::cout << "Test Rational<long> class less-than-or-equal-to operator...\n";

    // Both positive - easy comparison
    std::cout << "Compare two positive rational numbers:\n";
    Rational<long> r1(2, 3);
    Rational<long> r2(5, 7);
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


void testLongGreaterThanOrEqualToOperator() {
    std::cout << "Test  Rational<long> class greater-than-or-equal-to operator...\n";

    // Both positive - easy comparison
    std::cout << "Compare two positive rational numbers:\n";
    Rational<long> r1(2, 3);
    Rational<long> r2(5, 7);
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


void testLongCalculateMeanAverage() {
    std::cout << "\nTest the mean() function for a longRational<long> number...\n";

    Rational<long> collection[] = {
        Rational<long>(4l, 5l),
        Rational<long>(5l, 6l),
        Rational<long>(6l, 8l),
        Rational<long>(9l, 12l)
    };

    int numElements = std::size(collection);

    // Iterate through collection first
    std::cout << "There are " << numElements << " Rational<long> numbers in the collection.\n";
    std::cout << "The contents of the collection:\n\n";

    for (int i = 0; i < std::size(collection); ++i) {
        Rational<long>* current = collection + i;
        std::cout << "Element " << i << ": " << *current << '\n';
    }

    Rational<long> result = mean(collection, numElements);
    std::cout << "\nThe mean average of the collection is: " << result << '\n';    
}

void testLongMedian() {
    std::cout << "Test Rational class median() function (returns middle element of a sorted collection of Rational objects)...\n";

    // Array 1 - odd number of elements
    std::cout << "The first array has five elements (odd number), so the median element will be the one "
        << " in position 2 (after sorting)...\n";

    Rational<long> collection[] = { Rational<long>(2, 7),
        Rational<long>(2, 5), Rational<long>(10, 11),
        Rational<long>(4, 12), Rational<long>(4, 8) };

    int numElements = std::size(collection);
    std::cout << "There are " << numElements << " Rational<long> numbers in the collection.\n";

    std::cout << "\nThe contents of the collection before sorting:\n\n";

    for (int i = 0; i < std::size(collection); ++i) {
        Rational<long>* current = collection + i;
        std::cout << "Element " << i << ": " << *current << '\n';
    }

    // Sort the collection
    std::sort(collection, collection + numElements);

    // Iterate through collection first
    std::cout << "\nThe contents of the collection after sorting:\n\n";
    for (int i = 0; i < std::size(collection); ++i) {
        Rational<long>* current = collection + i;
        std::cout << "Element " << i << ": " << *current << '\n';
    }

    Rational<long> middle = median(collection, numElements);
    std::cout << "\nThe median element of the collection: " << middle << '\n';

    // There should be no risk of modifying the contents, but check anyway
    std::cout << "\nThe contents of the collection after calculating the median:\n\n";
    for (int i = 0; i < std::size(collection); ++i) {
        Rational<long>* current = collection + i;
        std::cout << "Element " << i << ": " << *current << '\n';
    }

    /*******************************************************************************/

    // Array 2 - an even number of elements
    std::cout << "\n\nThe first array has six elements (even number), so the median element "
        << "will be the sum of the elements in positions 2 and 3 (after sorting) divided by 2...\n";

    Rational<long> collection2[] = { Rational<long>(12, 13), 
       Rational<long>(3, 5), Rational<long>(10, 18),
       Rational<long>(4, 12), Rational<long>(4, 50), 
        Rational<long>(5, 6) };

    int numElements2 = std::size(collection2);
    std::cout << "There are " << numElements2 << " Rational<long> numbers in the collection.\n";

    std::cout << "\nThe contents of the second collection before sorting:\n\n";

    for (int i = 0; i < std::size(collection2); ++i) {
        Rational<long>* current = collection2 + i;
        std::cout << "Element " << i << ": " << *current << '\n';
    }

    // Sort the collection
    std::sort(collection2, collection2 + numElements2);

    // Iterate through collection first
    std::cout << "\nThe contents of the second collection after sorting:\n\n";
    for (int i = 0; i < std::size(collection2); ++i) {
        Rational<long>* current = collection2 + i;
        std::cout << "Element " << i << ": " << *current << '\n';
    }

    Rational<long> middle2 = median(collection2, numElements2);
    std::cout << "\nThe median element of the second collection: " << middle2 << '\n';

    // Check no elements have been modified
    std::cout << "\nThe contents of the second collection after calculating the median:\n\n";
    for (int i = 0; i < std::size(collection2); ++i) {
        Rational<long>* current = collection2 + i;
        std::cout << "Element " << i << ": " << *current << '\n';
    }
}