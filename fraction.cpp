#include <iostream>
#include <cmath>
#include "fraction.h"

Fraction sumA(int n) {
    if (n == 1) {
        return Fraction(1, 2);
    } else {
        Fraction sum{1, 2};
        for (int i = 2; i <= n; i++) {
            sum += Fraction(1, (i*(i+1))); 
        }
        return sum;
    }
}

//b 
Fraction sumB(int n) {
    if (n == 1) {
        return Fraction(1, 1);
    } else {
        Fraction sum{1, 1};
        for (int i = 2; i <= n; i++) {
            sum += Fraction(std::pow(-1, i+1), i); 
        }
        return sum;
    }
}

//c
Fraction sumC(int n) {
    if (n == 1) {
        return Fraction(1, 2);
    } else {
        Fraction sum{1, 2};
        for (int i = 2; i <= n; i++) {
            sum += Fraction(1, i*std::pow(2, i));
        }
        return sum;
    }
}

int main()
{
    constexpr Fraction f1{3, 8}, f2{1, 2}, f3{5, 4}, f4{5, 25};
    std::cout << f1 << " * " << f2 << " = " << f1 * f2 << '\n'
              <<  2 << " * " << f1 << " = " <<  2 * f1 << '\n'
              << f1 << " / " << f2 << " = " << f1 / f2 << '\n'
              << f2 << " / " << f3 << " = " << f2 / f3 << '\n'
              <<  2 << " + " << f1 << " = " <<  2 + f1 << '\n'
              << f4 << " + " << f1 << " = " << f4 + f1 << '\n'
              << f2 << " - " << f3 << " = " << f2 - f3 << '\n'
              << f4 << " - " << f1 << " = " << f4 - f1 << '\n'
              << "Numeryczna wartość " << f1 << " = " << f1.to_double() << '\n'
              << "Numeryczna wartość " << f3 << " = " << f3.to_double() << '\n';

    //a
    std::cout << "a)lim = " << 1 << '\n';
    for (int i = 1; i < 20; i+=3) {
        std::cout << "N = " << i << ", " << sumA(i) << " = " << sumA(i).to_double() << "\n";
    }
    //b)
    std::cout << "b)lim = " << std::log(2) << '\n';
    for (int i = 1; i < 20; i+=3) {
        std::cout << "N = " << i << ", " << sumB(i) << " = " << sumB(i).to_double() << "\n";
    }
    //c)
    std::cout << "c)lim = " << std::log(2) << '\n';
    for (int i = 1; i < 20; i+=3) {
        std::cout << "N = " << i << ", " << sumC(i) << " = " << sumC(i).to_double() << "\n";
    }
}
