# Library file name
NAME = libft.a

# Compiler and compilation flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Source files and object files
SRC = 		ft_isalpha.c ft_isdigit.c ft_isalmun.c ft_isascii.c ft_isprint.c \
			ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
			ft_strlcpy.c ft_strlcat.c\
			ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c  \
			ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c \
			ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
SRC_BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c \
			ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
			ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

## SRC = $(shell find . -type f -name "ft_*.c")
OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

# Name of the test executable
TEST_EXEC = test_libft
TEST_MAIN = main.c

# Indicate that the following rules are not actual files
.PHONY: all clean fclean re test bonus

# Default rule that compiles everything
all: $(NAME)

# Rule to create the library
$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

bonus: $(NAME) $(OBJ_BONUS)
	ar rcs $(NAME) $(OBJ_BONUS)

# Rule to compile the .c files into .o
# Included libft.h so that the Makefile automatically recompiles all the .o files.
%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

test: $(NAME)
	$(CC) $(CFLAGS) $(TEST_MAIN) -L. -lft -o $(TEST_EXEC)
	@echo "Running Test with $(TEST_MAIN):"
	./$(TEST_EXEC)

# Rule to delete all object files
clean:
	rm -f $(OBJ) $(OBJ_BONUS)

# Rule to delete all object files .o and executable file .a
fclean: clean
	rm -f $(NAME) $(TEST_EXEC)

re: fclean all
