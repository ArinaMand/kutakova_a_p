#include "stdafx.h"
#include "CppUnitTest.h"
#include "../rational/rational.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

template<>
inline std::wstring __cdecl Microsoft::VisualStudio::CppUnitTestFramework::ToString<Rational>(const Rational& t)
{
    // replace with your own, here is just my example
    RETURN_WIDE_STRING("qqqq");
}
namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestConstructDestruct)
		{

            Rational* object = new Rational();
            delete object;
            Rational object_1(5, 7);
            Rational object_2(25, 35);
            Assert::AreEqual(object_1, object_2);//check normalize()
            
            
        }
        TEST_METHOD(TestAriphmetic)
        {
            Rational object_1(5, 7);
            Rational object_2(25, 35);

            Rational object_3(2, 3);
            Rational object_4(29, 21);
            Rational object_5 = object_2;
            Assert::AreEqual(object_1, object_2);//check "="
            object_5 = object_1 + object_3;
            Assert::AreEqual(object_5, object_4);//check "+"
            object_5 = object_4 - object_3;
            Assert::AreEqual(object_5, object_1);//check "-"
            object_5 = object_1 * object_3;
            object_2 = Rational(10, 21);
            Assert::AreEqual(object_5, object_2);//check "*"
            object_5 = object_2 / object_3;
            Assert::AreEqual(object_5, object_1);//check "/"
            object_1 += object_3;
            Assert::AreEqual(object_1, object_4);//check "+="
            object_1 -= object_3;
            object_2 = Rational(5, 7);
            Assert::AreEqual(object_1, object_2);//check "-="
            object_1 *= object_3;
            object_5 = Rational(10, 21);
            Assert::AreEqual(object_1, object_5);//check "*="
            object_1 /= object_3;
            Assert::AreEqual(object_1, object_2);//check "/="
        }
        TEST_METHOD(TestLogic) {
            Rational object_1(5, 7);
            Rational object_2(25, 35);

            Rational object_3(2, 3);
            Rational object_4 = -object_1;
            Rational object_5(-5, 7);
            Assert::AreEqual(object_4, object_5);//check "-"
            
            Assert::AreEqual(object_1 == object_2, true);
            Assert::AreEqual(object_1 != object_2, false);
            Assert::AreEqual(object_1 == object_3, false);
            Assert::AreEqual(object_1 != object_3, true);
            Assert::AreEqual(object_1 > object_3, true);
            Assert::AreEqual(object_1 < object_3, false);
            Assert::AreEqual(object_1 >= object_2, true);
            Assert::AreEqual(object_1 <= object_3, false);
            //Assert::AreEqual(object_5 <= object_2, true);
        }
        TEST_METHOD(TestDouble) {
            Rational object_1 = Rational(5, 7);
            double object_val = object_1.toDouble();
            double doub_val = 5.0 / 7.0;
            Assert::AreEqual(object_val, doub_val);
        }
        TEST_METHOD(TestNumenatorDenominator) {
            Rational object = Rational(12, 37);
            int num = object.num();
            int true_num = 12;
            int denum = object.denum();
            int true_denum = 37;
            Assert::AreEqual(num, true_num);
            Assert::AreEqual(denum, true_denum);
        }
	};
}