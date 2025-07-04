NAME = btc

CXX = c++

CXXFLAGS = -Wall -Werror -Wextra -g -std=c++98

SRC = main.cpp \
		BitcoinExchange.cpp
	
OBJ = $(SRC:.cpp=.o)

HEADER = BitcoinExchange.hpp

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

%o: %cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re