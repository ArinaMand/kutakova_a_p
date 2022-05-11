#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest/doctest.h"
#include "rational.h"
#include <sstream>
#include <iosfwd>
TEST_CASE("Test arithmetics") {
Rational a(1, 2), b(1, 3);
CHECK(a + b == Rational(5, 6));
CHECK(a - b == Rational(1, 6));
CHECK(a * b == Rational(1, 6));
CHECK(a / b == Rational(3, 2));
a += b;
CHECK(a == Rational(5, 6));
a -= b;
a -= b;
CHECK(a == Rational(1, 6));
a += b;
a *= b;
CHECK(a == Rational(1, 6));
a /= b;
a /= b;
CHECK(a == Rational(3, 2));
}

TEST_CASE("Test comparison") {
    Rational a(1, 2), b(1, 3);
    CHECK_FALSE(a == b);
    CHECK_FALSE(a < b);
    CHECK_FALSE(a <= b);
    CHECK(a > b);
    CHECK(a != b);
    CHECK(a >= b);
    Rational c(0, 5), d(0, 9);
    CHECK_FALSE(c != d);
    //CHECK_FALSE(0 != d);
}

TEST_CASE("Test divide by zero") {
    Rational a(1, 2), b(0, 3);
    CHECK_THROWS(a / b);
    CHECK_THROWS(Rational(1, 0));
}

TEST_CASE("Test reduce") {
    Rational a(2, 2), b(-3, 3);
    CHECK(a == 1);
    CHECK(b == -a);
}