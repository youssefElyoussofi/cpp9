#ifndef BitcoinExchange_hpp
#define BitcoinExchange_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <deque>
#include <utility>
#include <map>
#include <iomanip>

class BitcoinExchange
{
    private:
        std::map<std::string,double> db;
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& bitcoinEx);
        BitcoinExchange& operator=(const BitcoinExchange& bitcoinEx);
        ~BitcoinExchange();
        class BtcException : public std::exception
        {
            private:
                std::string error;
            public:
                BtcException(std::string error);
                virtual ~BtcException() throw();
                virtual const char* what() const throw();
        };
        void exchange(const char* inputFile);
    };

#endif