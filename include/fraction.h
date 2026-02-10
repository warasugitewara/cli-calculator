#pragma once

#include <string>
#include <cmath>

class Fraction {
public:
    long long numerator;      // 分子
    long long denominator;    // 分母
    bool isValid;
    
    Fraction();
    Fraction(long long num, long long den = 1);
    Fraction(double value);
    
    // 分数操作
    void simplify();  // 約分
    double toDecimal() const;
    std::string toString() const;
    std::string toMixedString() const;  // 帯分数形式
    
    // 演算
    Fraction operator+(const Fraction& other) const;
    Fraction operator-(const Fraction& other) const;
    Fraction operator*(const Fraction& other) const;
    Fraction operator/(const Fraction& other) const;
    
    // 比較
    bool operator==(const Fraction& other) const;
    bool operator!=(const Fraction& other) const;
    
private:
    long long gcd(long long a, long long b) const;
};
