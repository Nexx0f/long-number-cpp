#include "NumberLibrary.hpp"
#include <iostream>

using namespace numlib;

int TAB_LEVEL = 0;

void print_tabs()
{
    for (int i = 0; i < TAB_LEVEL; i++)
        printf("  ");
}

char GROUP_FAILED = 0;
int GROUPS_FAILED = 0;

#define verify(condition) \
    if (!(condition)) \
    { \
        print_tabs(); \
        std::cout << "verification failed: '" << #condition << "' is false" << std::endl; \
        GROUP_FAILED = 1; \
        break; \
    } \
    else \
    { \
        print_tabs(); \
        std::cout << "verification ok: '" << #condition << "%s'" << std::endl; \
    }

#define begin_test_group(name) \
    { \
        GROUP_FAILED = 0; \
        TAB_LEVEL++; \
        std::cout << "Test group '" << name << "'" << std::endl; \
        do \
        {

#define end_test_group() \
        } \
        while (0); \
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

void testNumberCreation()
{
    begin_test_group("number creation");
    
    Number x(12);
    verify(x[0] == 2 && x[1] == 1);
    
    end_test_group();
}

void runUnitTests()
{
    testNumberCreation();
}

int main()
{
    runUnitTests();
    
    if (GROUPS_FAILED > 0)
        return 1;
    
    return 0;
}
