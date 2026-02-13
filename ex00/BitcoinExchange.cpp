#include "BitcoinExchange.hpp"
#include <cstring>
#include <vector>

BitcoinExchange::BitcoinExchange()
{
    std::ifstream dbfile("data.csv");

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


static void check_line(const std::string& line)
{
    std::vector<std::string> tokens;
    tokens.reserve(3);
    char *tmp = new char[line.length()];
    for (size_t i = 0; i < line.length(); i++)
    {
        tmp[i] = line[i];
    }

    char *str = strtok(tmp," ");
    while (str)
    {
        tokens.push_back(str);
        str = strtok(NULL," ");
    }
    for (size_t i = 0; i < tokens.size(); i++)
    {
        std::cout << tokens.at(i) << "\n";
    }
}

void BitcoinExchange::exchange(const char* inputFile)
{
    std::ifstream inputData(inputFile);

    if (!inputData.is_open())
        throw BitcoinExchange::BtcException("failed to open input file");
    // std::string line;

    // std::getline(inputData,line);
    // while (std::getline(inputData,line))
    // {
    //     std::cout << line << '\n';
    // }

    check_line("           2011-01-03           |         3          fghdfgh");

    inputData.close();
}
