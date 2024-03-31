/*
Implementacja klasy Fraction reprezentującej ułamki.
Obsługa operatorów + += - -= / /= * *= << == != oraz składowej to_double() zwracającej numeryczną wartość ułamka jako liczbę typu double.
*/

#include <iostream>
#include <cmath>

class Fraction
{
    constexpr int64_t gcd(int64_t a, int64_t b) { 
        return b == 0 ? a : gcd(b, a % b); 
    }

    int64_t n, d;
public:
    constexpr Fraction(int64_t n, int64_t d = 1) : n(n/gcd(n, d)), d(d/gcd(n, d)) {}

    constexpr int64_t numerator() const { return n; }
    constexpr int64_t denominator() const { return d; }

    constexpr Fraction& operator+=(const Fraction& rhs) {// a/b + c/d = (a*d + b*c) / (b*d)
        int64_t new_n = n * rhs.d + rhs.n * d;
        int64_t new_d = d * rhs.d;
        n = new_n / gcd(new_n, new_d);
        d = new_d / gcd(new_n, new_d);
        return *this;
    }

    constexpr Fraction& operator-=(const Fraction& rhs) {// a/b - c/d = (a*d - b*c) / (b*d)
        int64_t new_n = n * rhs.d - rhs.n * d;
        int64_t new_d = d * rhs.d;
        n = new_n / gcd(new_n, new_d);
        d = new_d / gcd(new_n, new_d);
        return *this;
    }

    constexpr Fraction& operator*=(const Fraction& rhs) {// (a/b) * (c/d) = (a*c) / (b*d)
        n = n * rhs.n / gcd(n* rhs.n, d * rhs.d);
        d = d * rhs.d / gcd(n* rhs.n, d * rhs.d);
        return *this;
    }

    constexpr Fraction& operator/=(const Fraction& rhs) {// (a/b) / (c/d) = (a*d) / (b*c)
        n = n * rhs.d / gcd(n* rhs.d, d * rhs.n);
        d = d * rhs.n / gcd(n* rhs.d, d * rhs.n);
        return *this;
    }

    constexpr double to_double() const {
        return static_cast<double>(n) / d;
    }

};

std::ostream& operator<<(std::ostream& out, const Fraction& f) {
   return out << f.numerator() << '/' << f.denominator();
}

constexpr bool operator==(const Fraction& lhs, const Fraction& rhs) {
    return lhs.numerator() == rhs.numerator() && lhs.denominator() == rhs.denominator();
}

constexpr bool operator!=(const Fraction& lhs, const Fraction& rhs) {
    return !(lhs == rhs);
}

constexpr Fraction operator+(Fraction lhs, const Fraction& rhs) {
    return lhs += rhs;
}

constexpr Fraction operator-(Fraction lhs, const Fraction& rhs){
    return lhs -= rhs;
}

constexpr Fraction operator*(Fraction lhs, const Fraction& rhs) {
    return lhs *= rhs;
}

constexpr Fraction operator/(Fraction lhs, const Fraction& rhs) {
    return lhs /= rhs;
}
