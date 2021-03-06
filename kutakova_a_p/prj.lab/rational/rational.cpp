#include "rational.h"
#include <iostream>
#include <math.h>
#include <string>

Rational::Rational(const int num, const int den) : numerator(num), denominator(den)
{
    if (0 == den) {
        throw std::invalid_argument("denominator must be not null");
    }
    normalize();
}
//Rational::Rational(const int num) : numerator(num), denominator(1) {};
Rational::Rational() = default;
Rational::Rational(const Rational& x) : numerator(x.numerator), denominator(x.denominator) {};
Rational::Rational(Rational&& x) = default;
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
    if (right.numerator == 0){
        throw std::invalid_argument("denominator must be not null");
    }
    numerator = numerator * right.denominator;
    denominator *= right.numerator;
    normalize();
    return *this;
};


Rational& Rational::operator+=(const int& right) {
    numerator = numerator + right*denominator;
    normalize();
    return *this;
};
Rational& Rational::operator-=(const int& right) {
    numerator = numerator - right*denominator;
    normalize();
    return *this;
};
Rational& Rational::operator*=(const int& right) {
    numerator = numerator * right;
    normalize();
    return *this;
};
Rational& Rational::operator/=(const int& right) {
    denominator *= right;
    normalize();
    return *this;
};


const Rational Rational::operator-() {
    return Rational(-numerator, denominator);
};

Rational& Rational::operator=(const Rational& right) {
    numerator = right.numerator;
    denominator = right.denominator;
    return *this;
};

Rational& Rational::operator=(Rational&& right) {
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
    if (denominator < 0){
        numerator *= -1;
        denominator *= -1;
    }
    int divider = NOD(abs(numerator), abs(denominator));
    while (abs(divider) > 1) {
        numerator /= divider;
        denominator /= divider;
        divider = NOD(abs(numerator), abs(denominator));
    }
};

std::ostream& Rational::write_to(std::ostream& strm) const {
    std::string str = std::to_string(numerator) + "/" + std::to_string(denominator);
    strm << str;
    return strm;
}

std::istream& Rational::read_from(std::istream& strm) {
    char c;
    int num;
    int den;
    strm >> num >> std::noskipws >> c >> den >> std::skipws;
    if (strm.fail()) {
        return strm;
    }
    if (c != '/' || den <= 0) {
        strm.setstate(std::ios_base::failbit);
        return strm;
    }
    *this = Rational(num, den);
}

std::ostream& operator<<(std::ostream& ostr, const Rational& r){
    return r.write_to(ostr);
}
std::istream& operator>>(std::istream& ostr, Rational& r){
    return r.read_from(ostr);
}

const Rational operator+(const Rational& left, const Rational& right)
{
    return Rational(left) += right;
}
const Rational operator-(const Rational& left, const Rational& right)
{
    return Rational(left) -= right;
}
const Rational operator*(const Rational& left, const Rational& right)
{
    return Rational(left) *= right;
}
const Rational operator/(const Rational& left, const Rational& right)
{
    return Rational(left) /= right;
}

const Rational operator+(const Rational& left, const int& right)
{
    return Rational(left) += right;
}
const Rational operator-(const Rational& left, const int& right)
{
    return Rational(left) -= right;
}
const Rational operator*(const Rational& left, const int& right)
{
    return Rational(left) *= right;
}
const Rational operator/(const Rational& left, const int& right)
{
    return Rational(left) /= right;
}

const Rational operator+(const int& left, const Rational& right)
{
    return Rational(left)+=right;
}
const Rational operator-(const int& left, const Rational& right)
{
    return Rational(left) -= right;
}
const Rational operator*(const int& left, const Rational& right)
{
    return Rational(left) *= right;
}
const Rational operator/(const int& left, const Rational& right)
{
    return Rational(left) /= right;
}