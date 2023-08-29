NAME := cub3D

SRC := main.c flood_fill.c grid_ops.c getters.c draw.c init_graphics.c main_loop.c
OBJ := $(SRC:%.c=%.o)

MLX_FW		:= -framework Cocoa -framework OpenGL -framework IOKit
MLX_LIB		:= -lglfw -L ~/.brew/opt/glfw/lib
MLX_NAME	:= ./MLX42/build/libmlx42.a
FT_DIR		:= ./libft
FT_SRC_DIR	:= $(FT_DIR)/src
LIBFT_NAME	:= $(FT_DIR)/build/libft.a
LFT_FLAG	:= -L$(FT_DIR)/build/ -lft
CC			:= cc
INCLUDE		:= -I$(FT_SRC_DIR) $(MLX_FW) $(MLX_NAME) $(MLX_LIB)
CFLAGS		:= -Wall -Werror -Wextra -g3 $(INCLUDE) #-fsanitize=address

all: $(NAME)

$(NAME): $(LIBFT_NAME) $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(LFT_FLAG) -o $(NAME)

$(LIBFT_NAME):
	make -C ./libft

%.o: %.c
	$(CC) -c $< -o $@

clean:
	make clean -C $(FT_DIR)
	/bin/rm -f $(OBJ)

fclean: clean
	make fclean -C $(FT_DIR)
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
