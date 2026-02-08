#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
    (void)av;
    if(ac != 2)
    {
        std::cerr << "program must take inputfile in argement\n";
        return 1;
    }
    try
    {
        BitcoinExchange btc;
        
        std::map<std::string,std::string>::iterator it = btc.db.begin();

        for (; it != btc.db.end(); it++)
        {
            std::cout << it->first << ' ' << it->second << '\n';
        }
        
        
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
    }
    return 0;
}