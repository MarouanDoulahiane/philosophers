DIR = src/
SRC = $(wildcard $(DIR)*.c)

NAME = philo

all:
	@cc -Wall -Werror -Wextra $(SRC) -o philo
clean:

fclean: clean

re: fclean all