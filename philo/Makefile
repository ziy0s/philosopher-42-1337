NAME= philo

CC= cc

MDR= main.c ft_atoi.c ft_alloc.c print.c ft_utils.c threads.c

OBJ=$(MDR:%.c=%.o)

CFLAG= -Wall -Wextra -Werror -pthread
# -fsanitize=thread  -g // you can use this to detect data races
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAG) $(OBJ) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAG) -c $< -o $@

clean:
	rm -rif $(OBJ)

fclean: clean
	rm -rif $(NAME)

re: fclean all
