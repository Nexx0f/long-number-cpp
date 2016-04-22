#pragma once

#include <exception>

namespace numlib
{
    
enum class NumberError
{
    // failed to parse number
    ERROR_INVALID_FORMAT,
    
    // division by zero
    ERROR_DIVISION_BY_ZERO,
    
    // when using operator[]
    ERROR_INDEX_OUT_OF_BOUNDS,
    
    // when using UnsignedNumber constructor with signed ints
    ERROR_NEGATIVE_NUMBER,
    
    // null pointer / etc.
    ERROR_INVALID_ARGUMENT
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
