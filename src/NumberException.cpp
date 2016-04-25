#include "NumberException.hpp"

using namespace numlib;

numlib::NumberException::NumberException(NumberError error):
    error(error)
{}

const char* numlib::NumberException::what() const noexcept
{
    switch (error)
    {
        case NumberError::INVALID_FORMAT: return "invalid format (failed to parse number)";
        case NumberError::DIVISION_BY_ZERO: return "division by zero";
        case NumberError::INDEX_OUT_OF_BOUNDS: return "index out of bounds";
        case NumberError::NEGATIVE_NUMBER: return "negative value can not be represented";
        case NumberError::INVALID_ARGUMENT: return "invalid argument";
    }
    
    return "";
}

NumberError numlib::NumberException::getError() const
{
    return error;
}
