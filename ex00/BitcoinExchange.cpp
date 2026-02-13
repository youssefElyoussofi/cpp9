#include "BitcoinExchange.hpp"
#include <cstring>
#include <vector>

enum Date {YEAR,MONTH,DAY};

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


static void check_number(const std::string& strNum,const Date& date)
{
    char* tmp = NULL;
    long nb = strtol(strNum.c_str(),&tmp,10);
    if (tmp != NULL)
        throw BitcoinExchange::BtcException("date number not valid");
    if (date == YEAR && (nb > 2026 || nb < 2008))
        throw BitcoinExchange::BtcException("date number not valid");
    if (date == MONTH && (nb > 12 || nb < 1))
        throw BitcoinExchange::BtcException("date number not valid"); 
    if (date == DAY && (nb > 31 || nb < 1))
        throw BitcoinExchange::BtcException("date number not valid");
}


static void check_date_format(const std::string& data)
{
    if (data.length() != 10 || data[4] != '-' || data[7] != '-') // XXXX-XX-XX
    {
        throw BitcoinExchange::BtcException("date format not valid");
    }
    check_number(data.substr(0,4),YEAR);
    check_number(data.substr(5,2),MONTH);
    check_number(data.substr(8,2),DAY);
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
    delete[] tmp;
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
    check_date_format("2011-01-03");

    inputData.close();
}
