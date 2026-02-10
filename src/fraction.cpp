#include "fraction.h"
#include <algorithm>
#include <sstream>
#include <iomanip>

Fraction::Fraction() : numerator(0), denominator(1), isValid(true) {}

Fraction::Fraction(long long num, long long den) 
    : numerator(num), denominator(den), isValid(true) {
    if (denominator == 0) {
        isValid = false;
        return;
    }
    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }
    simplify();
}

Fraction::Fraction(double value) : isValid(true) {
    // 小数を分数に変換
    const long long PRECISION = 1000000000000LL;  // 12桁の精度
    long long scaled = static_cast<long long>(std::round(value * PRECISION));
    numerator = scaled;
    denominator = PRECISION;
    simplify();
}

long long Fraction::gcd(long long a, long long b) const {
    a = std::abs(a);
    b = std::abs(b);
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void Fraction::simplify() {
    if (denominator == 0) {
        isValid = false;
        return;
    }
    long long g = gcd(numerator, denominator);
    if (g > 0) {
        numerator /= g;
        denominator /= g;
    }
    if (denominator < 0) {
        numerator = -numerator;
        denominator = -denominator;
    }
}

double Fraction::toDecimal() const {
    if (denominator == 0) return 0.0;
    return static_cast<double>(numerator) / static_cast<double>(denominator);
}

std::string Fraction::toString() const {
    if (denominator == 1) {
        return std::to_string(numerator);
    }
    return std::to_string(numerator) + "/" + std::to_string(denominator);
}

std::string Fraction::toMixedString() const {
    if (denominator == 1) {
        return std::to_string(numerator);
    }
    
    long long intPart = numerator / denominator;
    long long remPart = std::abs(numerator % denominator);
    
    if (intPart == 0) {
        return std::to_string(numerator) + "/" + std::to_string(denominator);
    }
    
    if (remPart == 0) {
        return std::to_string(intPart);
    }
    
    return std::to_string(intPart) + " " + std::to_string(remPart) + "/" + std::to_string(denominator);
}

Fraction Fraction::operator+(const Fraction& other) const {
    long long num = numerator * other.denominator + other.numerator * denominator;
    long long den = denominator * other.denominator;
    return Fraction(num, den);
}

Fraction Fraction::operator-(const Fraction& other) const {
    long long num = numerator * other.denominator - other.numerator * denominator;
    long long den = denominator * other.denominator;
    return Fraction(num, den);
}

Fraction Fraction::operator*(const Fraction& other) const {
    long long num = numerator * other.numerator;
    long long den = denominator * other.denominator;
    return Fraction(num, den);
}

Fraction Fraction::operator/(const Fraction& other) const {
    if (other.numerator == 0) {
        Fraction invalid;
        invalid.isValid = false;
        return invalid;
    }
    long long num = numerator * other.denominator;
    long long den = denominator * other.numerator;
    return Fraction(num, den);
}

bool Fraction::operator==(const Fraction& other) const {
    return numerator == other.numerator && denominator == other.denominator;
}

bool Fraction::operator!=(const Fraction& other) const {
    return !(*this == other);
}
