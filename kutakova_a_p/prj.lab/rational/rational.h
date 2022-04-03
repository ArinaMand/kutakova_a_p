#pragma once

#include <iostream>

class __declspec(dllexport) Rational {
public:
    Rational(const int num, const int den = 1);
    Rational(const int num);
    Rational();
    Rational(const Rational& x);
    ~Rational();

    Rational& operator+=(const Rational& right);
    Rational& operator-=(const Rational& right);
    Rational& operator*=(const Rational& right);
    Rational& operator/=(const Rational& right);


    Rational operator-();
    //Rational& operator=(const Rational& right);
    Rational& operator=(Rational& right);

    int num() const;
    int denum() const;


    bool operator==(const Rational& right) const;
    bool operator!=(const Rational& right) const;
    bool operator<(const Rational& right) const;
    bool operator>(const Rational& right) const;
    bool operator<=(const Rational& right) const;
    bool operator>=(const Rational& right) const;

    double toDouble();

private:
    int numerator = 0;
    int denominator = 1; // знаменатель >0
    int NOD(int a, int b);
    void normalize();
};

Rational operator+(const Rational& left, const Rational& right)
{
    return Rational(left) += right;
}
//inline Rational operator-(const Rational& left, const Rational& right);
//inline Rational operator*(const Rational& left, const Rational& right);
//inline Rational operator/(const Rational& left, const Rational& right);
Rational operator-(const Rational& left, const Rational& right)
{
    return Rational(left) -= right;
}
Rational operator*(const Rational& left, const Rational& right)
{
    return Rational(left) *= right;
}
Rational operator/(const Rational& left, const Rational& right)
{
    return Rational(left) /= right;
}


std::ostream& operator<<(std::ostream& ostr, const Rational& r);
std::istream& operator>>(std::istream& ostr, Rational& r);
