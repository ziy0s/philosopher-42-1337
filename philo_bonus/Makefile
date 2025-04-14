NAME = philo_bonus

CC = cc

CFLAG = -Wall -Wextra -Werror

FILE = main.c ft_atoi.c ft_alloc.c ft_utils.c print.c

OBJ = $(FILE:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAG) $(OBJ) -o $(NAME)

%.o: %.c philo_bonus.h
	$(CC) $(CFLAG) -c $< -o $@

clean:
	rm -rif $(OBJ)

fclean: clean
	rm -rif $(NAME)

re: fclean all