#include "BitcoinExchange.hpp"
#include <cstring>
#include <cstdlib>
#include <vector>
#include <limits.h>
#include <utility>

enum Number {YEAR,MONTH,DAY,VALUE};

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
        double price = strtod(second.c_str(),NULL);
        this->db.insert(std::pair<std::string,double>(first,price));
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


BitcoinExchange::BtcException::BtcException(std::string error):error(error)
{

}

BitcoinExchange::BtcException::~BtcException() throw(){}

const char* BitcoinExchange::BtcException::what() const throw()
{
    return this->error.c_str();
}



static double check_number(const std::string& strNum,const Number& num, const std::string& src)
{
    char* tmp = NULL;
    double nb = strtod(strNum.c_str(),&tmp);
    if (*tmp != '\0')
        throw BitcoinExchange::BtcException("bad input => " + src);
    if (num == MONTH && (nb > 12 || nb < 1))
        throw BitcoinExchange::BtcException("bad input => " + src); 
    if (num == DAY && (nb > 31 || nb < 1))
        throw BitcoinExchange::BtcException("number not valid");
    if (num == VALUE && nb < 0)
        throw BitcoinExchange::BtcException("not a positive number");
    if (num == VALUE && nb > INT_MAX)
        throw BitcoinExchange::BtcException("too large a number");
    return nb;
}


static void check_date_format(const std::string& data)
{
    if (data.length() != 10 || data[4] != '-' || data[7] != '-') // XXXX-XX-XX
    {
        throw BitcoinExchange::BtcException("date format not valid");
    }
    check_number(data.substr(0,4),YEAR,data);
    check_number(data.substr(5,2),MONTH,data);
    check_number(data.substr(8,2),DAY,data);
}   


static std::pair<std::string,double> check_line(const std::string& line)
{
    std::vector<std::string> tokens;
    tokens.reserve(3);
    char *tmp = new char[line.length() + 1];
    std::strcpy(tmp,line.c_str());

    char *str = strtok(tmp," ");
    while (str)
    {
        tokens.push_back(str);
        str = strtok(NULL," ");
    }
    delete[] tmp;
    if (tokens.size() != 3 || tokens.at(1) != "|")
        throw BitcoinExchange::BtcException("invalid line input must be \"date | value\"");
    check_date_format(tokens.at(0));
    double total = check_number(tokens.at(2),VALUE,tokens.at(2));
    return std::pair<std::string,double>(tokens.at(0),total);
}

void BitcoinExchange::exchange(const char* inputFile)
{
    std::ifstream inputData(inputFile);

    if (!inputData.is_open())
        throw BitcoinExchange::BtcException("failed to open input file");
    std::string line;

    std::getline(inputData,line);
    while (std::getline(inputData,line))
    {
        try
        {
            std::pair<std::string, double> p;
            p = check_line(line);
            std::map<std::string,double>::iterator it;
            it = this->db.upper_bound(p.first);
            if (it->first == p.first)
                std::cout << it->first << " => " << p.second << " = " << it->second * p.second << '\n';
            else if (it != this->db.begin())
            {
                it--;
                std::cout << it->first << " => " << p.second << " = " << it->second * p.second << '\n';
            }
            else
                std::cerr << "Error: no date found\n";
        }
        catch(const std::exception& e)
        {
            std::cerr << "Error: " << e.what() << '\n';
        }
    }
    inputData.close();
}
