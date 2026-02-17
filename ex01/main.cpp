#include "RPN.hpp"
#include <iostream>

int main(int ac, char* av[])
{
    if (ac != 2)
    {
        std::cerr << "enter inverted Polish mathematical expression as argement";
        return 1;
    }
    Rpn rpn;
    try
    {
        rpn.processPolishEX(av[1]);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}