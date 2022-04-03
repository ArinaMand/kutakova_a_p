#include "stdafx.h"
#include "CppUnitTest.h"
#include "../rational/rational.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{

            Rational object;
            delete &object;
            Rational object_1(5, 7);
            Rational object_2(25, 37);
            Assert::AreEqual(object_1, object_2);//check normalize()
            Rational object_3(2, 3);
            Rational object_4(29, 21);
            Rational object_5;
            object_5 = object_1 + object_3;
            Assert::AreEqual(object_1+object_3, object_4);//check "+"
            Assert::AreEqual(object_4-object_3, object_1);//check "-"
            Assert::AreEqual(object_1*object_3, object_2);//check "*"
            Assert::AreEqual(object_2/object_3, object_1);//check "/"
            Assert::AreEqual(object_5, object_4);//check "="
            object_1 += object_3;
            Assert::AreEqual(object_1, object_4);//check "+="
            object_1 -= object_3;
            Assert::AreEqual(object_1, Rational(5, 7));//check "-="
            object_1 *= object_3;
            Assert::AreEqual(object_1, object_4);//check "*="
            object_1 /= object_3;
            Assert::AreEqual(object_1, Rational(5, 7));//check "/="
            
            object_5 = Rational(-5, 7);
            Assert::AreEqual(-object_1, object_5);//check "-"

            Assert::AreEqual(object_1 == object_2, true);
            Assert::AreEqual(object_1 != object_2, false);
            Assert::AreEqual(object_1 == object_3, false);
            Assert::AreEqual(object_1 != object_3, true);
            Assert::AreEqual(object_1 > object_2, true);
            Assert::AreEqual(object_1 < object_2, false);
            Assert::AreEqual(object_1 >= object_2, true);
            Assert::AreEqual(object_1 <= object_2, false);
            Assert::AreEqual(object_5 <= object_2, true);
            
            double doub_val = 5.0 / 7.0;
            Assert::AreEqual(object_1.toDouble(), doub_val);
        }

	};
}