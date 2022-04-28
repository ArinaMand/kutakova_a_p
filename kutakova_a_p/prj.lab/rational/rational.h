#include <iostream>

class Rational {
public:
    Rational(const int num, const int den = 1);
    Rational(const int num);
    Rational();
    Rational(const Rational& x);
    Rational(Rational&& x);
    ~Rational();

    Rational& operator+=(const Rational& right);
    Rational& operator-=(const Rational& right);
    Rational& operator*=(const Rational& right);
    Rational& operator/=(const Rational& right);


    const Rational operator-();
    Rational& operator=(const Rational& right);
    Rational& operator=(Rational&& right);

    int num() const;
    int denum() const;


    bool operator==(const Rational& right) const;
    bool operator!=(const Rational& right) const;
    bool operator<(const Rational& right) const;
    bool operator>(const Rational& right) const;
    bool operator<=(const Rational& right) const;
    bool operator>=(const Rational& right) const;

    double toDouble();

    std::ostream& write_to(std::ostream& strm) const;
    std::istream& read_from(std::istream& strm);

private:
    int numerator = 0;
    int denominator = 1; // ����������� >0
    int NOD(int a, int b);
    void normalize();
};

const Rational operator+(const Rational& left, const Rational& right);
const Rational operator-(const Rational& left, const Rational& right);
const Rational operator*(const Rational& left, const Rational& right);
const Rational operator/(const Rational& left, const Rational& right);


std::ostream& operator<<(std::ostream& ostr, const Rational& r);
std::istream& operator>>(std::istream& ostr, Rational& r);
