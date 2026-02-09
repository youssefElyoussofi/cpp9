#include "BitcoinExchange.hpp"

const char* BitcoinExchange::dbFileName = "data.csv";

BitcoinExchange::BitcoinExchange()
{
    std::ifstream dbfile(dbFileName);

    if (!dbfile.is_open())
        throw BitcoinExchange::BtcException("failed load database");

    std::string line;
    getline(dbfile,line);
    while (getline(dbfile,line))
    {
        size_t pos =  line.find(',');
        std::string first = line.substr(0,pos);
        std::string second = line.substr(pos + 1,line.length());
        this->db.insert({first,second});
    }
    dbfile.close();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& bitcoinEx)
{
    (void)bitcoinEx;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& bitcoinEx)
{
    (void)bitcoinEx;
    return *this;
}

BitcoinExchange::~BitcoinExchange()
{

}


BitcoinExchange::BtcException::BtcException(const char* error):error(error)
{

}

const char* BitcoinExchange::BtcException::what() const throw()
{
    return this->error;
}


void BitcoinExchange::exchange(const char* inputFile)
{
    std::ifstream inputData(inputFile);

    if (!inputData.is_open())
        throw BitcoinExchange::BtcException("failed to open input file");

    
    inputData.close();
}
