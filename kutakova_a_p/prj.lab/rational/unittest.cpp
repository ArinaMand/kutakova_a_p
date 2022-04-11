#include "rational.h"
#include <cassert>
#include <iostream>

void TestConstructDestruct()
{

    Rational* object = new Rational();
    delete object;
    Rational object_1(5, 7);
    Rational object_2(25, 35);
    assert(object_1 == object_1);
    assert(object_1 == object_2);//assert normalize()
}
void TestAriphmetic()
{
    Rational object_1(5, 7);
    Rational object_2(25, 35);

    Rational object_3(2, 3);
    Rational object_4(29, 21);
    Rational object_5 = object_2;
    assert(object_1== object_2);//assert "="
    object_5 = object_1 + object_3;
    assert(object_5== object_4);//assert "+"
    object_5 = object_4 - object_3;
    assert(object_5== object_1);//assert "-"
    object_5 = object_1 * object_3;
    object_2 = Rational(10, 21);
    assert(object_5== object_2);//assert "*"
    object_5 = object_2 / object_3;
    assert(object_5== object_1);//assert "/"
    object_1 += object_3;
    assert(object_1== object_4);//assert "+="
    object_1 -= object_3;
    object_2 = Rational(5, 7);
    assert(object_1== object_2);//assert "-="
    object_1 *= object_3;
    object_5 = Rational(10, 21);
    assert(object_1== object_5);//assert "*="
    object_1 /= object_3;
    assert(object_1== object_2);//assert "/="
}
void TestLogic() {
    Rational object_1(5, 7);
    Rational object_2(25, 35);

    Rational object_3(2, 3);
    Rational object_4 = -object_1;
    Rational object_5(-5, 7);
    assert(object_4== object_5);//assert "-"

    assert((object_1 == object_2) == true);
    assert((object_1 != object_2) == false);
    assert((object_1 == object_3) == false);
    assert((object_1 != object_3) == true);
    assert((object_1 > object_3) == true);
    assert((object_1 < object_3) == false);
    assert((object_1 >= object_2) == true);
    assert((object_1 <= object_3) == false);
    assert((object_5 <= object_2) == true);
}
void TestDouble() {
    Rational object_1 = Rational(5, 7);
    double object_val = object_1.toDouble();
    double doub_val = 5.0 / 7.0;
    assert(object_val== doub_val);
}
void TestNumenatorDenominator() {
    Rational object = Rational(12, 37);
    int num = object.num();
    int true_num = 12;
    int denum = object.denum();
    int true_denum = 37;
    assert(num== true_num);
    assert(denum== true_denum);
}

int main(){
    TestConstructDestruct();
    TestAriphmetic();
    TestLogic();
    TestDouble();
    TestNumenatorDenominator();
}
