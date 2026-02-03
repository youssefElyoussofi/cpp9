CXX=c++
CXXFLAGS=-Wall -Wextra -Werror -std=c++98
SRC=BitcoinExchange.cpp main.cpp
OBJ=$(SRC:.cpp=.o)
NAME=btc

$(NAME):$(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re