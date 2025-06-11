// Rational Version 2
// ------------------
// 
// This file is for tests of the version of the Rational class that uses 
// C++20's spaceship operator, obviating the need to define (all) 
// the equality/comparison operators.
// 
// The tests here are purely on the spaceship operator and the separately defined
// less-than operator, since the class is otherwise identical to the first version 
// of the Rational class.

#include <iostream>
#include "Rational_v2.h"

void testSpaceshipOperator();


int main() {
    testSpaceshipOperator();
}


void testSpaceshipOperator() {
    std::cout << "Test Rational class spaceship operator...\n\n";

    Rational r1(3, 4);
    Rational r2(9, 14);

    std::cout << "r1: " << r1 << '\n';
    std::cout << "r2: " << r2 << '\n';

    std::cout << std::boolalpha;

    // These six comparisions use the spaceship operator.
    // The spaceship operator uses a default equality operator as basis
    // for less-than. 
    // Therefore we get the WRONG results in these cases.
    // The less-than comparison must be customised.
    auto result1 = ((r1 <=> r2) > 0);
    std::cout << "\n\nr1 > r2:     " << result1 << '\n';

    // Wrong result(rational as above).
    auto result2 = ((r1 <=> r2) >= 0);
    std::cout << "r1 >= r2:    " << result2 << '\n';

    // Equality is correct.
    auto result3 = (r1 == r2);
    std::cout << "r1 == r2:    " << result3 << '\n';

    // Inequality is correct.
    auto result4 = (r1 != r2);
    std::cout << "r1 != r2:    " << result4 << '\n';

    // Wrong result (rational as above).
    auto result5 = ((r1 <=> r2) < 0);
    std::cout << "r1 < r2:     " << result5 << '\n';

    // Wrong result(rational as above).
    auto result6 = ((r1 <=> r2) <= 0);
    std::cout << "r1 <= r2:    " << result6 << '\n';

    // These two comparisons use the the custom less-than operator, 
    // so the results are correct.
    auto result7 = (r1 < r2);
    std::cout << "r1 < r2:     " << result7 << '\n';

    auto result8 = (r2 < r1);
    std::cout << "r2 < r1:     " << result8 << '\n';

    /*************** Implicit conversions *************************************/

    std::cout << "\n\nTest implicit conversions:\n";
    auto result9 = (r1 > 10);
    std::cout << "(r1 > 10) =  " << result9 << '\n';

    auto result10 = (10 < r1);  // ( 10 <=> r1) < 0
    std::cout << "(10 < r1) =  " << result10 << '\n';

    auto result11 = (r2 != 12);
    std::cout << "(r2 != 12) = " << result11 << '\n';

    auto result12 = (12 != r2);
    std::cout << "(12 != r2) = " << result12 << '\n';

    auto result13 = (r1 < 0);
    std::cout << "(r1 < 0) =   " << result13 << '\n';
}