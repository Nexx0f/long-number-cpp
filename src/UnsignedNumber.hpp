#pragma once

#include <iostream>
#include <vector>
#include <string>

namespace numlib
{

class UnsignedNumber
{
    std::vector<unsigned> digits;
    
    void shrinkLeadingZeros();
    
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
    UnsignedNumber& operator/=(const UnsignedNumber& rhs);
    UnsignedNumber& operator*=(const UnsignedNumber& rhs);
    
    bool isZero() const;
    
    void appendDigit(int digit);
};

UnsignedNumber operator+(UnsignedNumber lhs, const UnsignedNumber& rhs);
UnsignedNumber operator-(UnsignedNumber lhs, const UnsignedNumber& rhs);
UnsignedNumber operator/(UnsignedNumber lhs, const UnsignedNumber& rhs);
UnsignedNumber operator*(UnsignedNumber lhs, const UnsignedNumber& rhs);

bool operator==(const UnsignedNumber& lhs, const UnsignedNumber& rhs);
bool operator!=(const UnsignedNumber& lhs, const UnsignedNumber& rhs);
bool operator<(const UnsignedNumber& lhs, const UnsignedNumber& rhs);
bool operator>(const UnsignedNumber& lhs, const UnsignedNumber& rhs);
bool operator<=(const UnsignedNumber& lhs, const UnsignedNumber& rhs);
bool operator>=(const UnsignedNumber& lhs, const UnsignedNumber& rhs);

std::istream& operator>>(std::istream& in, UnsignedNumber& num);
std::ostream& operator<<(std::ostream& out, UnsignedNumber& num);

} // namespace numlib
