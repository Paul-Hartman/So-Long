
CC := cc


CFLAGS := -Wall -Wextra -Werror


SRCS := map.c game.c validation.c utils.c main.c rendering.c

ifeq ($(shell uname), Linux)
	INCLUDES = -I/usr/include -Imlx ./libft/libft.a game.h
else
	INCLUDES = -I/opt/X11/include -Imlx ./libft/libft.a game.h
endif



MLX_LIB = ./mlx/libmlx.a
LIBFT = ./libft/libft.a

ifeq ($(shell uname), Linux)
	MLX_FLAGS = -Lmlx -lmlx -L/usr/lib/X11 -lXext -lX11
else
	MLX_FLAGS = -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
endif

OBJS := $(SRCS:.c=.o)






NAME := so_long

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS)  $(OBJS) $(LIBFT) $(MLX_PATH) $(MLX_FLAGS) -o $(NAME) 
 
all: $(NAME) $(MLX_LIB) $(LIBFT) 
 
$(MLX_LIB):
	@make -C ./mlx

$(LIBFT):
	@make -C ./libft
	@make bonus -C ./libft
 

 


clean:
	rm -f $(OBJS)
	make clean -C ./libft
	make clean -C ./mlx
	

fclean: clean
	make fclean -C ./libft
	make clean -C ./mlx
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
