NAME= philo_bonus

CC= cc

MDR= main.c ft_time.c ft_simulation.c ft_output.c ft_init.c ft_atoi.c ft_alloc.c ft_utils.c ft_itoa.c

OBJ=$(MDR:%.c=%.o)

CFLAG= -Wall -Wextra -Werror -pthread

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