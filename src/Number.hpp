#pragma once

#include "UnsignedNumber.hpp"

namespace numlib
{

class Number : public UnsignedNumber
{
    bool isNegative;
    
public :
    
    Number();
    Number(const Number& num) = default;
    Number(const UnsignedNumber& num);
    Number(unsigned);
    Number(int);
    Number(std::string);
    
    ~Number() override;
    
    Number& operator=(const Number& lhs) = default;
    
    Number& operator+=(const Number& rhs);
    Number& operator-=(const Number& rhs);
    Number& operator/=(const Number& rhs);
    Number& operator*=(const Number& rhs);
    
    bool operator==(const Number& rhs) const;
    bool operator!=(const Number& rhs) const;
    bool operator<(const Number& rhs) const;
    bool operator>(const Number& rhs) const;
    bool operator<=(const Number& rhs) const;
    bool operator>=(const Number& rhs) const;
};

Number operator+(const Number& lhs, const Number& rhs);
Number operator-(const Number& lhs, const Number& rhs);
Number operator/(const Number& lhs, const Number& rhs);
Number operator*(const Number& lhs, const Number& rhs);

bool operator==(const Number& lhs, const Number& rhs);
bool operator!=(const Number& lhs, const Number& rhs);
bool operator<(const Number& lhs, const Number& rhs);
bool operator>(const Number& lhs, const Number& rhs);
bool operator<=(const Number& lhs, const Number& rhs);
bool operator>=(const Number& lhs, const Number& rhs);

std::istream& operator>>(std::istream& in, Number& num);
std::ostream& operator<<(std::ostream& out, Number& num);
    
} // namespace numlib
