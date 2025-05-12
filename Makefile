NAME = pipex
CC = gcc
CCFLAGS = -Wall -Werror -Wextra
SRC = 	src/pipex.c \
		src/parser.c \
		src/execute.c \
		src/utils.c
OBJ = $(SRC:.c=.o)
LIBFT = libft/libft.a
INCLUDES = -I include -I libft
RM = rm -f

all: $(NAME)

$(LIBFT):
	make -C libft

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CCFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CCFLAGS) $(INCLUDES) -c $< -o $@

clean:
	make clean -C libft
	$(RM) $(OBJ)

fclean: clean
	make fclean -C libft
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
