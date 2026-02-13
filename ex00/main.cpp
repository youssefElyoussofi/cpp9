#include "BitcoinExchange.hpp"
#include <vector>



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
    
        btc.exchange(av[1]);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
    }
    

    return 0;
}