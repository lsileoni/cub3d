NAME := cub3D

SRC := main.c flood_fill.c grid_ops.c getters.c draw.c init_graphics.c main_loop.c
OBJ := $(SRC:%.c=%.o)

MLX_FW			:= -framework Cocoa -framework OpenGL -framework IOKit
MLX_LIB			:= -lglfw -L ~/.brew/opt/glfw/lib
MLX_NAME		:= ./MLX42/build/libmlx42.a
FT_DIR			:= ./libft
FT_SRC_DIR		:= $(FT_DIR)/src
LIBFT_NAME		:= $(FT_DIR)/build/libft.a
LFT_FLAG		:= -L$(FT_DIR)/build/ -lft
CC				:= cc
INCLUDE_MACOS	:= -I$(FT_SRC_DIR) $(MLX_FW) $(MLX_NAME) $(MLX_LIB)
INCLUDE_LINUX	:= -I$(FT_SRC_DIR) $(MLX_NAME) $(MLX_LIB)
CFLAGS_MACOS	:= -Wall -Werror -Wextra -g3 $(INCLUDE_MACOS) #-fsanitize=address
CFLAGS_LINUX	:= -Wall -Werror -Wextra -g3 $(INCLUDE_LINUX) #-fsanitize=address

all: $(NAME)

linux: $(LIBFT_NAME) $(MLX_NAME) $(OBJ)
	$(CC) $(OBJ) $(CFLAGS_LINUX) $(LFT_FLAG) -o $(NAME)

$(NAME): $(LIBFT_NAME) $(MLX_NAME) $(OBJ)
	$(CC) $(OBJ) $(CFLAGS_MACOS) $(LFT_FLAG) -o $(NAME)

$(LIBFT_NAME):
	make -C ./libft

$(MLX_NAME):
	cd ./MLX42 && cmake -B build && cmake --build build -j4

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
