#include "rational.h"
#include <iostream>

TEST_CASE("TestConstructDestruct")
{

    Rational* object = new Rational();
    delete object;
    Rational object_1(5, 7);
    Rational object_2(25, 35);
    CHECK(object_1, object_2);//check normalize()
}
TEST_CASE("TestAriphmetic")
{
    Rational object_1(5, 7);
    Rational object_2(25, 35);

    Rational object_3(2, 3);
    Rational object_4(29, 21);
    Rational object_5 = object_2;
    CHECK(object_1, object_2);//check "="
    object_5 = object_1 + object_3;
    CHECK(object_5, object_4);//check "+"
    object_5 = object_4 - object_3;
    CHECK(object_5, object_1);//check "-"
    object_5 = object_1 * object_3;
    object_2 = Rational(10, 21);
    CHECK(object_5, object_2);//check "*"
    object_5 = object_2 / object_3;
    CHECK(object_5, object_1);//check "/"
    object_1 += object_3;
    CHECK(object_1, object_4);//check "+="
    object_1 -= object_3;
    object_2 = Rational(5, 7);
    CHECK(object_1, object_2);//check "-="
    object_1 *= object_3;
    object_5 = Rational(10, 21);
    CHECK(object_1, object_5);//check "*="
    object_1 /= object_3;
    CHECK(object_1, object_2);//check "/="
}
TEST_CASE("TestLogic") {
    Rational object_1(5, 7);
    Rational object_2(25, 35);

    Rational object_3(2, 3);
    Rational object_4 = -object_1;
    Rational object_5(-5, 7);
    CHECK(object_4, object_5);//check "-"

    CHECK(object_1 == object_2, true);
    CHECK(object_1 != object_2, false);
    CHECK(object_1 == object_3, false);
    CHECK(object_1 != object_3, true);
    CHECK(object_1 > object_3, true);
    CHECK(object_1 < object_3, false);
    CHECK(object_1 >= object_2, true);
    CHECK(object_1 <= object_3, false);
    //CHECK(object_5 <= object_2, true);
}
TEST_CASE("TestDouble") {
    Rational object_1 = Rational(5, 7);
    double object_val = object_1.toDouble();
    double doub_val = 5.0 / 7.0;
    CHECK(object_val, doub_val);
}
TEST_CASE("TestNumenatorDenominator") {
    Rational object = Rational(12, 37);
    int num = object.num();
    int true_num = 12;
    int denum = object.denum();
    int true_denum = 37;
    CHECK(num, true_num);
    CHECK(denum, true_denum);
}