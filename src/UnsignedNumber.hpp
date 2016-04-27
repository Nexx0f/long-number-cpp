#pragma once

#include <iostream>
#include <vector>
#include <string>

namespace numlib
{

class UnsignedNumber
{
protected :
    std::vector<unsigned> digits;
    
    void shrinkLeadingZeros();
    void divideNumbers(const UnsignedNumber& a, const UnsignedNumber& b, UnsignedNumber& quotient, UnsignedNumber& remainder);
    void shift(int by);
    
public :
    
    UnsignedNumber();
    UnsignedNumber(const UnsignedNumber& from) = default;
    UnsignedNumber(unsigned from);
    UnsignedNumber(int from);
    UnsignedNumber(std::string from);
    
    virtual ~UnsignedNumber();
    
    UnsignedNumber& operator=(const UnsignedNumber& lhs) = default;
    
    unsigned length() const;
    const std::vector<unsigned>& getDigits() const;
    
    unsigned& operator[](int index);
    const unsigned& operator[](int index) const;

    UnsignedNumber& operator+=(const UnsignedNumber& rhs);
    UnsignedNumber& operator-=(const UnsignedNumber& rhs);
    UnsignedNumber& operator*=(const UnsignedNumber& rhs);
    UnsignedNumber& operator/=(const UnsignedNumber& rhs);
    UnsignedNumber& operator%=(const UnsignedNumber& rhs);
};

UnsignedNumber operator+(UnsignedNumber lhs, const UnsignedNumber& rhs);
UnsignedNumber operator-(UnsignedNumber lhs, const UnsignedNumber& rhs);
UnsignedNumber operator*(UnsignedNumber lhs, const UnsignedNumber& rhs);
UnsignedNumber operator/(UnsignedNumber lhs, const UnsignedNumber& rhs);
UnsignedNumber operator%(UnsignedNumber lhs, const UnsignedNumber& rhs);

bool operator==(const UnsignedNumber& lhs, const UnsignedNumber& rhs);
bool operator!=(const UnsignedNumber& lhs, const UnsignedNumber& rhs);
bool operator<(const UnsignedNumber& lhs, const UnsignedNumber& rhs);
bool operator>(const UnsignedNumber& lhs, const UnsignedNumber& rhs);
bool operator<=(const UnsignedNumber& lhs, const UnsignedNumber& rhs);
bool operator>=(const UnsignedNumber& lhs, const UnsignedNumber& rhs);

std::istream& operator>>(std::istream& in, UnsignedNumber& num);
std::ostream& operator<<(std::ostream& out, const UnsignedNumber& num);

} // namespace numlib
