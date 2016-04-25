#include "UnsignedNumber.hpp"
#include "NumberException.hpp"

using namespace numlib;

int universalCompare(const std::vector<unsigned>& a, int aSign, const std::vector<unsigned>& b, int bSign);

numlib::UnsignedNumber::UnsignedNumber():
    UnsignedNumber(0)
{}

numlib::UnsignedNumber::UnsignedNumber(int from):
    UnsignedNumber(std::to_string(from))
{}

numlib::UnsignedNumber::UnsignedNumber(unsigned from):
    UnsignedNumber(std::to_string(from))
{}

numlib::UnsignedNumber::~UnsignedNumber()
{}

numlib::UnsignedNumber::UnsignedNumber(std::string from)
{
    if (from.empty())
        throw NumberException(NumberError::INVALID_FORMAT);
    
    if (from[0] == '+')
        from = from.substr(1);
    
    if (from[0] == '-')
        throw NumberException(NumberError::NEGATIVE_NUMBER);
    
    for (char& c: from)
        if (!isdigit(c))
            throw NumberException(NumberError::INVALID_FORMAT);
        
    digits.resize(from.length());
    for (unsigned i = 0; i < length(); i++)
        digits[i] = from[length() - i - 1] - '0';
}

unsigned numlib::UnsignedNumber::length() const
{
    return digits.size();
}

unsigned& numlib::UnsignedNumber::operator[](int index)
{
    if (index < 0 || index >= (int)length())
        throw NumberException(NumberError::INDEX_OUT_OF_BOUNDS);
    
    return digits[index];
}

const unsigned& numlib::UnsignedNumber::operator[](int index) const
{
    if (index < 0 || index >= (int)length())
        throw NumberException(NumberError::INDEX_OUT_OF_BOUNDS);
    
    return digits[index];
}

std::istream& numlib::operator>>(std::istream& in, numlib::UnsignedNumber& num)
{
    char first;
    in >> first;
    
    if (first == '-')
        throw NumberException(NumberError::NEGATIVE_NUMBER);
    else if (isdigit(first))
        in.unget();
    else
        throw NumberException(NumberError::INVALID_FORMAT);
    
    in >> first;
    while (isdigit(first))
    {
        num.appendDigit(first - '0');
        in >> first;
    }
    in.unget();
    
    return in;
}

void numlib::UnsignedNumber::appendDigit(int digit)
{
    if (digit < 0 || digit >= 10)
        throw NumberException(NumberError::INVALID_ARGUMENT);
    
    digits.push_back(digit);
}

void numlib::UnsignedNumber::shrinkLeadingZeros()
{
    while (digits.size() > 1 && !digits.back())
        digits.pop_back();
}

UnsignedNumber& numlib::UnsignedNumber::operator+=(const UnsignedNumber& rhs)
{
    digits.resize(digits.size() + 1);
    
    int carry = 0;
    for (unsigned i = 0; i < length(); i++)
    {
        carry += digits[i];
        if (i < rhs.length()) carry += rhs[i];
        
        digits[i] = carry % 10;
        carry /= 10;
    }
    
    shrinkLeadingZeros();
    return *this;
}

UnsignedNumber& numlib::UnsignedNumber::operator-=(const UnsignedNumber& rhs)
{
    if (*this < rhs)
        throw NumberException(NumberError::NEGATIVE_NUMBER);
    
    bool isCarry = 0;
    for (unsigned i = 0; i < length(); i++)
    {
        int digit = digits[i];
        
        if (isCarry && digit > 0)
        {
            isCarry = false;
            digit--;
        }
        
        if (isCarry)
            digit += 9;
        
        int needSub = i < rhs.length() ? rhs[i] : 0;
        
        if (needSub > digit)
        {
            digit += 10;
            isCarry = true;
        }
        
        digits[i] = digit - needSub;
    }
    
    shrinkLeadingZeros();
    return *this;
}

UnsignedNumber& numlib::UnsignedNumber::operator*=(const UnsignedNumber& rhs)
{
    UnsignedNumber res;
    
    res.digits.resize(length() + rhs.length() + 1);
    
    for (unsigned i = 0; i < length(); i++)
    {
        int carry = 0;
        
        for (unsigned j = i; j < res.length(); j++)
        {
            carry += res[j];
            
            if (j - i < rhs.length())
                carry += rhs[j - i] * digits[i];
            
            res[j] = carry % 10;
            carry /= 10;
        }
    }
    
    *this = res;
    shrinkLeadingZeros();
    return *this;
}

int universalCompare(const std::vector<unsigned>& a, int aSign, const std::vector<unsigned>& b, int bSign)
{
    unsigned aNonzero = a.size() - 1, bNonzero = b.size() - 1;
    
    while (aNonzero > 0 && a[aNonzero] == 0) aNonzero--;
    while (bNonzero > 0 && b[bNonzero] == 0) bNonzero--;
        
    bool aZero = aNonzero == 0 && a[aNonzero] == 0;
    bool bZero = bNonzero == 0 && b[bNonzero] == 0;
        
    if (aZero && bZero) return 0;
    
    if (aZero) return bSign;
    if (bZero) return aSign;
    
    if (aSign != bSign) return aSign;
    
    int noSignResult = 0;
    
    if (aNonzero == bNonzero)
    {
        for (int i = aNonzero; i >= 0; i--)
            if (a[i] != b[i])
            {
                noSignResult = a[i] > b[i] ? 1 : -1;
                break;
            }
    }
    else
    {
        noSignResult = aNonzero > bNonzero ? 1 : -1;
    }
    
    return noSignResult * aSign;
}

const std::vector<unsigned>& numlib::UnsignedNumber::getDigits() const
{
    return digits;
}

bool numlib::operator==(const UnsignedNumber& lhs, const UnsignedNumber& rhs)
{
    return universalCompare(lhs.getDigits(), 1, rhs.getDigits(), 1) == 0;
}

bool numlib::operator!=(const UnsignedNumber& lhs, const UnsignedNumber& rhs)
{
    return universalCompare(lhs.getDigits(), 1, rhs.getDigits(), 1) != 0;
}

bool numlib::operator<(const UnsignedNumber& lhs, const UnsignedNumber& rhs)
{
    return universalCompare(lhs.getDigits(), 1, rhs.getDigits(), 1) < 0;
}

bool numlib::operator>(const UnsignedNumber& lhs, const UnsignedNumber& rhs)
{
    return universalCompare(lhs.getDigits(), 1, rhs.getDigits(), 1) > 0;
}

bool numlib::operator<=(const UnsignedNumber& lhs, const UnsignedNumber& rhs)
{
    return universalCompare(lhs.getDigits(), 1, rhs.getDigits(), 1) <= 0;
}

bool numlib::operator>=(const UnsignedNumber& lhs, const UnsignedNumber& rhs)
{
    return universalCompare(lhs.getDigits(), 1, rhs.getDigits(), 1) >= 0;
}

UnsignedNumber numlib::operator+(UnsignedNumber lhs, const UnsignedNumber& rhs)
{
    lhs += rhs;
    return lhs;
}

UnsignedNumber numlib::operator-(UnsignedNumber lhs, const UnsignedNumber& rhs)
{
    lhs -= rhs;
    return lhs;
}

UnsignedNumber numlib::operator*(UnsignedNumber lhs, const UnsignedNumber& rhs)
{
    lhs *= rhs;
    return lhs;
}
