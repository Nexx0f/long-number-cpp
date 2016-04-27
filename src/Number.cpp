#include "Number.hpp"
#include "NumberException.hpp"

#include <algorithm>

using namespace numlib;

int universalCompare(const std::vector<unsigned>& a, int aSign, const std::vector<unsigned>& b, int bSign);

numlib::Number::Number(): UnsignedNumber(), isNegative(false) {}

numlib::Number::Number(const UnsignedNumber& num):
    UnsignedNumber(num), isNegative(false)
{}

numlib::Number::Number(int from):
    Number(std::to_string(from))
{}

numlib::Number::Number(unsigned from):
    UnsignedNumber(std::to_string(from)), isNegative(false)
{}

numlib::Number::Number(std::string from)
{
    bool negative = false;
    
    if (!from.empty() && (from[0] == '-' || from[0] == '+'))
    {
        negative = from[0] == '-';
        from = from.substr(1);
    }
    
    *this = UnsignedNumber(from);
    isNegative = negative;
}

int numlib::Number::sign() const
{
    return isNegative ? -1 : 1;
}

std::istream& numlib::operator>>(std::istream& in, numlib::Number& num)
{
    char first;
    in >> first;
    
    std::string digits = "";
    if (first == '-')
        digits = "-";
    
    if (first == '+' || first == '-')
        in >> first;

    if (!isdigit(first))
        throw NumberException(NumberError::INVALID_FORMAT);
    
    do
    {
        digits += first;
    }
    while (in >> first && isdigit(first));
    if (in.eof())
        in.unget();
    
    num = Number(digits);
    
    return in;
}

std::ostream& numlib::operator<<(std::ostream& out, const Number& num)
{
    if (num < 0)
        out << '-';
    out << (UnsignedNumber&)num;
    
    return out;
}

Number& numlib::Number::operator+=(const Number& rhs)
{
    if (isNegative == rhs.isNegative)
    {
        UnsignedNumber::operator+=(rhs);
        return *this;
    }

    if (isNegative)
    {
        Number sum = rhs;
        sum += *this;
        return *this = sum;
    }
    
    // a >= 0
    
    if (universalCompare(getDigits(), 1, rhs.getDigits(), 1) >= 0)
    {
        UnsignedNumber::operator-=(rhs);
        return *this;
    }
    
    *this = (const UnsignedNumber&)rhs - (const UnsignedNumber&)*this;
    isNegative = true;
    return *this;
}

Number& numlib::Number::operator-=(const Number& rhs)
{
    Number rhsCopy = rhs;
    rhsCopy.isNegative = true;
    return *this += rhsCopy;
}

Number& numlib::Number::operator*=(const Number& rhs)
{
    isNegative ^= rhs.isNegative;
    UnsignedNumber::operator*=(rhs);
    return *this;
}

Number numlib::Number::operator-() const
{
    Number res = *this;
    res.isNegative = !res.isNegative;
    return res;
}

bool numlib::operator==(const Number& lhs, const Number& rhs)
{
    return universalCompare(lhs.getDigits(), lhs.sign(), rhs.getDigits(), rhs.sign()) == 0;
}

bool numlib::operator!=(const Number& lhs, const Number& rhs)
{
    return universalCompare(lhs.getDigits(), lhs.sign(), rhs.getDigits(), rhs.sign()) != 0;
}

bool numlib::operator<(const Number& lhs, const Number& rhs)
{
    return universalCompare(lhs.getDigits(), lhs.sign(), rhs.getDigits(), rhs.sign()) < 0;
}

bool numlib::operator>(const Number& lhs, const Number& rhs)
{
    return universalCompare(lhs.getDigits(), lhs.sign(), rhs.getDigits(), rhs.sign()) > 0;
}

bool numlib::operator<=(const Number& lhs, const Number& rhs)
{
    return universalCompare(lhs.getDigits(), lhs.sign(), rhs.getDigits(), rhs.sign()) <= 0;
}

bool numlib::operator>=(const Number& lhs, const Number& rhs)
{
    return universalCompare(lhs.getDigits(), lhs.sign(), rhs.getDigits(), rhs.sign()) >= 0;
}

Number& Number::operator/=(const Number& rhs)
{
    Number q, r;
    divideNumbers(*this, rhs, q, r);
    q.isNegative = r.isNegative = isNegative ^ rhs.isNegative;
    return *this = q;
}

Number& Number::operator%=(const Number& rhs)
{
    Number q, r;
    divideNumbers(*this, rhs, q, r);
    q.isNegative = r.isNegative = isNegative ^ rhs.isNegative;
    return *this = r;
}

Number numlib::operator+(Number lhs, const Number& rhs)
{
    lhs += rhs;
    return lhs;
}

Number numlib::operator-(Number lhs, const Number& rhs)
{
    lhs -= rhs;
    return lhs;
}

Number numlib::operator*(Number lhs, const Number& rhs)
{
    lhs *= rhs;
    return lhs;
}

Number numlib::operator/(Number lhs, const Number& rhs)
{
    lhs /= rhs;
    return lhs;
}

Number numlib::operator%(Number lhs, const Number& rhs)
{
    lhs %= rhs;
    return lhs;
}
