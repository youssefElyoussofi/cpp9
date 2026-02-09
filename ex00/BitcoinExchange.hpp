#ifndef BitcoinExchange_hpp
#define BitcoinExchange_hpp

#include <iostream>
#include <fstream>
#include <string>
#include <map>

class BitcoinExchange
{
    private:
        std::map<std::string,std::string> db;
    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& bitcoinEx);
        BitcoinExchange& operator=(const BitcoinExchange& bitcoinEx);
        ~BitcoinExchange();
        class BtcException : public std::exception
        {
            private:
                const char* error;
            public:
                BtcException(const char* error);
                virtual const char* what() const throw();
        };
        static const char* dbFileName;
        void exchange(const char* inputFile);
    };

#endif