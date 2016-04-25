#pragma once

#include <exception>

namespace numlib
{
    
enum class NumberError
{
    // failed to parse number
    INVALID_FORMAT,
    
    // division by zero
    DIVISION_BY_ZERO,
    
    // when using operator[]
    INDEX_OUT_OF_BOUNDS,
    
    // when using UnsignedNumber constructor with signed ints
    // when substracting lower from greater
    NEGATIVE_NUMBER,
    
    // null pointer / etc.
    INVALID_ARGUMENT
};

class NumberException : public std::exception
{
    NumberError error;
    
public :
    NumberException(NumberError error);
    
    const char* what() const noexcept override;
    
    NumberError getError() const;
};
    
}
