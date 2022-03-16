#include "pch.h"
#include <iostream>


class Rational {
    public:
        Rational(const int num, const int den = 1) : numerator(num), denominator(den)
        {
            if (0 == den) {
                throw std::invalid_argument("denominator must be not null");
            }
            normalize();
        }
        Rational() = default;

        Rational(const Rational& x) : numerator(x.numerator), denominator(x.denominator) {};
        ~Rational() = default;

        Rational& operator+=(const Rational& right) {
            numerator = numerator * right.denominator + right.numerator*denominator;
            denominator *= right.denominator;
            normalize();
            return *this;
        };
        Rational& operator-=(const Rational& right) {
            numerator = numerator * right.denominator - right.numerator*denominator;
            denominator *= right.denominator;
            normalize();
            return *this;
        };
        Rational& operator*=(const Rational& right) {
            numerator = numerator * right.numerator;
            denominator *= right.denominator;
            normalize();
            return *this;
        };
        Rational& operator/=(const Rational& right) {
            numerator = numerator * right.denominator;
            denominator *= right.numerator;
            normalize();
            return *this;
        };
        

        Rational operator-() const {
            return Rational(-numerator, denominator);
        };
        Rational& operator=(const Rational& right) {
            numerator = right.numerator;
            denominator = right.denominator;
        };


        bool operator==(const Rational& right) const {
            return (numerator == right.numerator) && (denominator == right.denominator);
        };
        bool operator!=(const Rational& right) const {
            return (numerator != right.numerator) || (denominator != right.denominator);
        };
        bool operator<(const Rational& right) const {
            return numerator*right.denominator < right.numerator*denominator;
        };
        bool operator>(const Rational& right) const {
            return numerator * right.denominator > right.numerator*denominator;
        };
        bool operator<=(const Rational& right) const {
            return numerator * right.denominator <= right.numerator*denominator;
        };
        bool operator>=(const Rational& right) const {
            return numerator * right.denominator >= right.numerator*denominator;
        };

        
        double toDouble(){
            return (double)numerator / denominator;
        }

    private:
        int numerator = 0;
        int denominator = 1; // знаменатель >0
        int NOD(int a, int b) {
            if (a % b == 0)
                return b;
            if (b % a == 0)
                return a;
            if (a > b)
                return NOD(a%b, b);
            return NOD(a, b%a);
        };
        void normalize() {
            int divider = NOD(numerator, denominator);
            while (divider > 1) {
                numerator /= divider;
                denominator /= divider;
                divider = NOD(numerator, denominator);
            }
        };
};

Rational operator+(const Rational& left, const Rational& right)
{
    return Rational(left) += right;
}

std::ostream& operator<<(std::ostream& ostr, const Rational& r);

std::istream& operator>>(std::istream& ostr, Rational& r);



int main()
{
    std::cout << "Hello World!\n"; 
}
