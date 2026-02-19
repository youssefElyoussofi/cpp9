#include "RPN.hpp"
#include <string>
#include <exception>
#include <cstring>
#include <iostream>

Rpn::Rpn()
{

}

Rpn::Rpn(const Rpn& rpn):rpn(rpn.rpn)
{

}

Rpn& Rpn::operator=(const Rpn& rpn)
{
    if (this != &rpn)
        this->rpn = rpn.rpn;
    return *this;
}

Rpn::~Rpn() 
{

}

Rpn::RpnException::~RpnException() throw()
{

}

Rpn::RpnException::RpnException(const std::string& error):error(error)
{

}

const char* Rpn::RpnException::what() const throw()
{
    return this->error.c_str();
}


void Rpn::calculate(operat op)
{
    if (rpn.size() < 2)
        throw Rpn::RpnException("No Enough Numbers for Calculation");
    int second = rpn.top();
    rpn.pop();
    int first = rpn.top();
    rpn.pop();
    int res;
    if (op == ADD)
        res = first + second;
    else if (op == SUM)
        res = first - second;
    else if (op == MULTI)
        res = first * second;
    else if (op == DIV)
    {
        if (second == 0)
            throw Rpn::RpnException("Cannot Divide by 0");
        res = first / second;
    }
    rpn.push(res);
}

void Rpn::processPolishEX(const std::string& str)
{
    std::string allowed = "0123456789+-/* ";
    
    for (size_t i = 0; i < str.length(); i++)
    {
        if (allowed.find(str[i]) == std::string::npos)
            throw Rpn::RpnException("Invalid Input");
    }
    for(size_t i = 0;i < str.length();i++)
    {
        if (isdigit(str[i]))
            rpn.push(str[i] - '0');
        else if (str[i] == '+')
            calculate(ADD);
        else if (str[i] == '-')
            calculate(SUM);
        else if (str[i] == '*')
            calculate(MULTI);
        else if (str[i] == '/')
            calculate(DIV);
    }
    std::cout << rpn.top() << '\n';
}

