#include "NumberLibrary.hpp"
#include <iostream>

using namespace numlib;

int TAB_LEVEL = 0;

void printTabs()
{
    for (int i = 0; i < TAB_LEVEL; i++)
        printf("  ");
}

bool GROUP_FAILED = 0;
int GROUPS_FAILED = 0;

#define verify(condition) \
    if (!(condition)) \
    { \
        printTabs(); \
        std::cout << "verification failed: '" << #condition << "' is false" << std::endl; \
        GROUP_FAILED = true; \
        break; \
    } \
    else \
    { \
        printTabs(); \
        std::cout << "verification ok: '" << #condition << "'" << std::endl; \
    }
    
#define verify_exception(code,err) \
    try\
    {\
        code; \
        printTabs(); \
        std::cout << "verification failed: exception expected." << std::endl; \
        GROUP_FAILED = true; \
        break; \
    }\
    catch(NumberException& e)\
    {\
        if (e.getError() != NumberError::err) \
        { \
            printTabs(); \
            std::cout << "verification failed: exception caught ('" << e.what() << "'), but its error code is different from '" \
                << #err << "'" << std::endl; \
            GROUP_FAILED = true; \
            break; \
        } \
        else \
        { \
            printTabs(); \
            std::cout << "verification ok, desired exception caught ('" << e.what() << "')." << std::endl; \
        } \
    }

#define begin_test_group(name) \
    { \
        GROUP_FAILED = false; \
        TAB_LEVEL++; \
        std::cout << "Test group '" << name << "'" << std::endl; \
        try\
        {\
            do \
            {

#define end_test_group() \
            } \
            while (0); \
        } \
        catch (std::exception& e) \
        { \
            std::cout << "unexpected exception: " << e.what() << std::endl; \
            GROUP_FAILED = true; \
        } \
        TAB_LEVEL--; \
        if (GROUP_FAILED) \
        { \
            std::cout << "test group failed" << std::endl; \
            GROUPS_FAILED++; \
        } \
        else \
        { \
            std::cout << "test group ok" << std::endl; \
        } \
    }

#define check_ok() verify(long_number_errno == ERROR_OK);

void testUnsignedCreation()
{
    begin_test_group("unsigned creation");
    
    {
        UnsignedNumber x(12);
        verify(x[0] == 2 && x[1] == 1);
        
        x = UnsignedNumber(12u);
        verify(x[0] == 2 && x[1] == 1);
        
        x = UnsignedNumber("+100");
        verify(x[0] == 0 && x[1] == 0 && x[2] == 1);
        
        const UnsignedNumber& constRef = x;
        verify(constRef[0] == 0 && constRef[1] == 0 && constRef[2] == 1);
        verify_exception(constRef[3], INDEX_OUT_OF_BOUNDS);
        
        x = UnsignedNumber();
        verify(x[0] == 0);
        
        x = UnsignedNumber("0");
        verify(x[0] == 0);
    }
    
    verify_exception(UnsignedNumber(-12), NEGATIVE_NUMBER);
    verify_exception(UnsignedNumber("124abc"), INVALID_FORMAT);
    verify_exception(UnsignedNumber(""), INVALID_FORMAT);
    verify_exception(UnsignedNumber("123")[3], INDEX_OUT_OF_BOUNDS);
    verify_exception(UnsignedNumber("123")[-1], INDEX_OUT_OF_BOUNDS);
    
    end_test_group();
}

void testUnsignedComparison()
{
    begin_test_group("number comparison");
    
    verify(UnsignedNumber("100234234234") == UnsignedNumber("100234234234"));
    verify(!(UnsignedNumber("1") == UnsignedNumber("2")));
    verify(UnsignedNumber("1") != UnsignedNumber("2"));
    verify(!(UnsignedNumber("100234234234") != UnsignedNumber("100234234234")));
    verify(UnsignedNumber("1") < UnsignedNumber("2"));
    verify(!(UnsignedNumber("2") < UnsignedNumber("1")));
    verify(UnsignedNumber("200") > UnsignedNumber("1"));
    verify(!(UnsignedNumber("1") > UnsignedNumber("200")));
    verify(UnsignedNumber("200") >= UnsignedNumber("200"));
    verify(!(UnsignedNumber("200") >= UnsignedNumber("201")));
    verify(UnsignedNumber("200") <= UnsignedNumber("200"));
    verify(UnsignedNumber("200") <= UnsignedNumber("1000"));
    
    end_test_group();
}

UnsignedNumber operator"" _n (const char* str)
{
    return UnsignedNumber(str);
}

void testUnsignedArithmetics()
{
    begin_test_group("unsigned arithmetics");
    verify(10_n + 10_n == 20_n);
    verify(0_n + 0_n == 0_n);
    verify(11_n + 9_n == 20_n);
    verify(11_n - 2_n == 9_n);
    verify(1010_n - 101_n == 909_n);
    verify(100000_n - 1_n == 99999_n);
    verify_exception(100_n - 200_n, NEGATIVE_NUMBER);
    
    verify(9_n * 9_n == 81_n);
    verify(23423_n * 234234_n == 5486462982_n);
    verify(10_n * 0_n == 0_n);
    verify(0_n * 10_n == 0_n);
    
    end_test_group();
}

void runUnitTests()
{
    testUnsignedCreation();
    testUnsignedComparison();
    testUnsignedArithmetics();
}

int main()
{
    runUnitTests();
    
    if (GROUPS_FAILED > 0)
        return 1;
    
    return 0;
}
