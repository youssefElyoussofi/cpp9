#include <stack>
#include <string>
#include <exception>

enum operat {ADD,SUM,MULTI,DIV};


class Rpn 
{
    private:
        std::stack<int> rpn;
        void calculate(operat ex);
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
                virtual ~RpnException() throw();
                RpnException(const std::string& error);
                virtual const char* what() const throw();
        };
        void processPolishEX(const std::string& str);
};