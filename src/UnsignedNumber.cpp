#include "UnsignedNumber.hpp"
#include "NumberException.hpp"

using namespace numlib;

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
