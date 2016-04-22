#pragma once

#include <iostream>
#include <vector>
#include <string>

namespace numlib
{

class UnsignedNumber
{
    std::vector<unsigned> digits;
    
public :
    
    UnsignedNumber();
    UnsignedNumber(const UnsignedNumber& from);
    UnsignedNumber(unsigned from);
    UnsignedNumber(int from);
    UnsignedNumber(std::string from);
    
    virtual ~UnsignedNumber();
    
    UnsignedNumber& operator=(const UnsignedNumber& lhs);
    
    unsigned length() const;
    
    unsigned& operator[](int index);
    const unsigned& operator[](int index) const;

    UnsignedNumber& operator+=(const UnsignedNumber& rhs);
    UnsignedNumber& operator-=(const UnsignedNumber& rhs);
    UnsignedNumber& operator/=(const UnsignedNumber& rhs);
    UnsignedNumber& operator*=(const UnsignedNumber& rhs);
    
    bool isZero() const;
};

UnsignedNumber operator+(const UnsignedNumber& lhs, const UnsignedNumber& rhs);
UnsignedNumber operator-(const UnsignedNumber& lhs, const UnsignedNumber& rhs);
UnsignedNumber operator/(const UnsignedNumber& lhs, const UnsignedNumber& rhs);
UnsignedNumber operator*(const UnsignedNumber& lhs, const UnsignedNumber& rhs);

bool operator==(const UnsignedNumber& lhs, const UnsignedNumber& rhs);
bool operator!=(const UnsignedNumber& lhs, const UnsignedNumber& rhs);
bool operator<(const UnsignedNumber& lhs, const UnsignedNumber& rhs);
bool operator>(const UnsignedNumber& lhs, const UnsignedNumber& rhs);
bool operator<=(const UnsignedNumber& lhs, const UnsignedNumber& rhs);
bool operator>=(const UnsignedNumber& lhs, const UnsignedNumber& rhs);

std::istream& operator>>(std::istream& in, UnsignedNumber& num);
std::ostream& operator<<(std::ostream& out, UnsignedNumber& num);

} // namespace numlib
