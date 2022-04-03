#include "pch.h"
#include "rational.h"
#include <iostream>
#include <math.h>

Rational::Rational(const int num, const int den) : numerator(num), denominator(den)
{
    if (0 == den) {
        throw std::invalid_argument("denominator must be not null");
    }
    normalize();
}
Rational::Rational(const int num) : numerator(num), denominator(1) {};
Rational::Rational() = default;

Rational::Rational(const Rational& x) : numerator(x.numerator), denominator(x.denominator) {};
Rational::~Rational() = default;

Rational& Rational::operator+=(const Rational& right) {
    numerator = numerator * right.denominator + right.numerator*denominator;
    denominator *= right.denominator;
    normalize();
    return *this;
};
Rational& Rational::operator-=(const Rational& right) {
    numerator = numerator * right.denominator - right.numerator*denominator;
    denominator *= right.denominator;
    normalize();
    return *this;
};
Rational& Rational::operator*=(const Rational& right) {
    numerator = numerator * right.numerator;
    denominator *= right.denominator;
    normalize();
    return *this;
};
Rational& Rational::operator/=(const Rational& right) {
    numerator = numerator * right.denominator;
    denominator *= right.numerator;
    normalize();
    return *this;
};
        

Rational Rational::operator-() {
    return Rational(-numerator, denominator);
};
/*
Rational& Rational::operator=(const Rational& right) {
    numerator = right.numerator;
    denominator = right.denominator;
    return *this;
};
*/
Rational& Rational::operator=(Rational& right) {
    numerator = right.numerator;
    denominator = right.denominator;
    return *this;
};

int Rational::num() const {
    return numerator;
}
int Rational::denum() const {
    return denominator;
}


bool Rational::operator==(const Rational& right) const {
    return (numerator == right.numerator) && (denominator == right.denominator);
};
bool Rational::operator!=(const Rational& right) const {
    return (numerator != right.numerator) || (denominator != right.denominator);
};
bool Rational::operator<(const Rational& right) const {
    return numerator*right.denominator < right.numerator*denominator;
};
bool Rational::operator>(const Rational& right) const {
    return numerator * right.denominator > right.numerator*denominator;
};
bool Rational::operator<=(const Rational& right) const {
    return numerator * right.denominator <= right.numerator*denominator;
};
bool Rational::operator>=(const Rational& right) const {
    return numerator * right.denominator >= right.numerator*denominator;
};

        
double Rational::toDouble(){
    return (double)numerator / denominator;
}

int Rational::NOD(int a, int b) {
    if (a % b == 0)
        return b;
    if (b % a == 0)
        return a;
    if (a > b)
        return NOD(a%b, b);
    return NOD(a, b%a);
};
void Rational::normalize() {
    int divider = NOD(abs(numerator), abs(denominator));
    while (abs(divider) > 1) {
        numerator /= divider;
        denominator /= divider;
        divider = NOD(numerator, denominator);
    }
};

/*
Rational operator+(const Rational& left, const Rational& right)
{
    return Rational(left) += right;
}

inline Rational operator-(const Rational& left, const Rational& right)
{
    return Rational(left) -= right;
}
inline Rational operator*(const Rational& left, const Rational& right)
{
    return Rational(left) *= right;
}
inline Rational operator/(const Rational& left, const Rational& right)
{
    return Rational(left) /= right;
}

*/
std::ostream& operator<<(std::ostream& ostr, const Rational& r);

std::istream& operator>>(std::istream& ostr, Rational& r);



int main()
{
    std::cout << "Hello World!\n"; 
}
