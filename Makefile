# Compiler
CC := cc

# Compiler flags
CFLAGS := -Wall -Wextra -Werror

# Source files
SRCS := map.c

# Object files
OBJS := $(SRCS:.c=.o)

# Library name
LIB_NAME := libft.a

# Target
NAME := program

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -g -o $@ $^ -Llibft -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

$(LIB_NAME): $(OBJS)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -Ilibft -Imlx_linux -O3 -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) $(LIB_NAME)

re: fclean all

.PHONY: all clean fclean re
