#ifndef BitcoinExchange_hpp
#define BitcoinExchange_hpp

// #include <vector>
#include <string>

class BitcoinExchange
{

    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange& bitcoinEx);
        BitcoinExchange& operator=(const BitcoinExchange& bitcoinEx);
        ~BitcoinExchange();
        BitcoinExchange(std::string input, std::string db);
};

#endif