NAME = philo
AR = ar -rcs
CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread #Iinc no necesario porq mi .h no está dentro de una carpeta llamada inc
SRC = philo.c parser.c utils.c philo_threads.c init.c actions.c
OBJ = $(SRC:.c=.o)
all: $(NAME)

$(NAME): $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re