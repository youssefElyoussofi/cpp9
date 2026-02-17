#include "RPN.hpp"
#include <string>
#include <exception>
#include <cstring>

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

Rpn::RpnException::RpnException(const std::string& error):error(error)
{

}

const char* Rpn::RpnException::what() const throw()
{
    return this->error.c_str();
}



void Rpn::processPolishEX(const std::string& str)
{
    std::string allowed = "0123456789+-/* ";
    
    if(str.find_first_not_of(allowed))
        throw Rpn::RpnException("Invalid input");
    
    for(size_t i = 0;i < str.length();i++)
    {
        
    }
    
}

