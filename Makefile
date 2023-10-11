NAME := cub3D

SRC :=	src/main.c \
		src/raycasting/ray.c \
		src/raycasting/dda.c \
		src/raycasting/endpoint.c \
		src/raycasting/setters.c \
		src/raycasting/ray_utils.c \
		src/parsing/flood_fill.c \
		src/parsing/grid_ops.c \
		src/parsing/get_grid.c \
		src/parsing/get_textures.c \
		src/parsing/init_info.c \
		src/parsing/parsing_utils.c \
		src/graphics/init_graphics.c \
		src/graphics/hooks.c \

OBJDIR := ./obj
SRCDIR := ./src
OBJ := $(addprefix $(OBJDIR)/,$(SRC:.c=.o))
DEP := $(OBJ:%.o=%.d)

MLX_FW			:= -framework Cocoa -framework OpenGL -framework IOKit -lm
MLX_LIB			:= -lglfw -L ~/.brew/opt/glfw/lib -lm
MLX_NAME		:= ./MLX42/build/libmlx42.a
FT_DIR			:= ./libft
FT_SRC_DIR		:= $(FT_DIR)/src
LIBFT_NAME		:= $(FT_DIR)/build/libft.a
LFT_FLAG		:= -L$(FT_DIR)/build/ -lft
CC				:= cc
SHARED			:= -Wall -Wextra -Werror -Ofast -march=native
INCLUDE_MACOS	:= -I$(FT_SRC_DIR) $(MLX_FW) $(MLX_NAME) $(MLX_LIB)
INCLUDE_LINUX	:= -I$(FT_SRC_DIR) $(MLX_NAME) $(MLX_LIB)
INCLUDE_LIBFT	:= -I./libft/src/
INCLUDE_MLX		:= -I./MLX42/include/MLX42/
INCLUDE_LOCAL	:= -I./includes/
HEADERS			:=  $(INCLUDE_LIBFT) $(INCLUDE_MLX) $(INCLUDE_LOCAL)
CFLAGS_MACOS	:= $(SHARED) $(INCLUDE_MACOS) $(HEADERS)
CFLAGS_LINUX	:= $(SHARED) $(INCLUDE_LINUX) $(HEADERS)

all: $(NAME)

linux: $(LIBFT_NAME) $(MLX_NAME) $(OBJ)
	$(CC) $(OBJ) $(CFLAGS_LINUX) $(LFT_FLAG) -o $(NAME)

$(NAME): $(LIBFT_NAME) $(MLX_NAME) $(OBJ)
	$(CC) $(OBJ) $(CFLAGS_MACOS) $(LFT_FLAG) -o $(NAME)

$(LIBFT_NAME):
	make -C ./libft

$(MLX_NAME):
	cd ./MLX42 && cmake -B build && cmake --build build -j4

-include $(DEP)

$(OBJDIR)/%.o: %.c
	@$(shell [ ! -d $(@D) ] && mkdir -p $(@D))
	$(CC) $(SHARED) $(HEADERS) -MMD -c $< -o $@

clean:
	make clean -C $(FT_DIR)
	/bin/rm -rf $(OBJDIR)

fclean: clean
	make fclean -C $(FT_DIR)
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re linux
