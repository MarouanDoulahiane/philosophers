DIR = src/
SRC = $(wildcard $(DIR)*.c)

NAME = philo

all:
	@cc -Wall -Werror -Wextra $(SRC)
clean:

fclean: clean

re: fclean all