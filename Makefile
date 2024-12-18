NAME =  PmergeMe

CC = c++

FLAGS = -Wall -Wextra -Werror -std=c++98

SRC = main.cpp	PmergeMe.cpp

OBJ = ${SRC:.cpp=.o}


%.o : %.cpp
	$(CC) $(FLAGS) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

clean :
	rm -f $(OBJ)

fclean :
	rm -f $(OBJ) $(NAME)

re : fclean all
