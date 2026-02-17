#include <stack>

class Rpn 
{
    private:
        std::stack<int> rpn;
    public:
        Rpn();
        Rpn(const Rpn& rpn);
        Rpn& operator=(const Rpn& rpn);
        ~Rpn();
        class RpnException : public std::exception
        {
            private:
                std::string error;
            public:
                RpnException(const std::string& error);
                virtual const char* what() const throw();
        };
        void processPolishEX(const std::string& str);
};