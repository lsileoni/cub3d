NAME := cub3D

FILES :=	src/main \
		src/raycasting/ray \
		src/raycasting/dda \
		src/raycasting/endpoint \
		src/raycasting/setters \
		src/raycasting/ray_utils \
		src/parsing/flood_fill \
		src/parsing/grid_ops \
		src/parsing/get_grid \
		src/parsing/get_textures \
		src/parsing/init_info \
		src/parsing/parsing_utils \
		src/parsing/vec_utils \
		src/graphics/init_graphics \
		src/graphics/hooks \

SRC := $(addsuffix .c,$(FILES))
BSRC := $(addsuffix _bonus.c,$(FILES))

OBJDIR := ./obj
SRCDIR := ./src
OBJ := $(addprefix $(OBJDIR)/,$(SRC:.c=.o))
BOBJ := $(addprefix $(OBJDIR)/,$(BSRC:.c=.o))
DEP := $(OBJ:%.o=%.d)
BDEP := $(BOBJ:%.o=%.d)

MLX_LIB			:= -lglfw -L ~/.brew/opt/glfw/lib -lm
MLX_NAME		:= ./MLX42/build/libmlx42.a
FT_DIR			:= ./libft
FT_SRC_DIR		:= $(FT_DIR)/src
LIBFT_NAME		:= $(FT_DIR)/build/libft.a
LFT_FLAG		:= -L$(FT_DIR)/build/ -lft
CC				:= cc
SHARED			:= -Wall -Wextra -Werror -Ofast -march=native
INCLUDE_MACOS	:= -I$(FT_SRC_DIR) $(MLX_NAME) $(MLX_LIB)
INCLUDE_LINUX	:= -I$(FT_SRC_DIR) $(MLX_NAME) $(MLX_LIB)
INCLUDE_LIBFT	:= -I./libft/src/
INCLUDE_MLX		:= -I./MLX42/include/MLX42/
INCLUDE_LOCAL	:= -I./includes/
HEADERS			:= $(INCLUDE_LIBFT) $(INCLUDE_MLX) $(INCLUDE_LOCAL)
CFLAGS 			:= $(SHARED) $(INCLUDE_MACOS) $(HEADERS)

all: $(NAME)

bonus: fclean $(LIBFT_NAME) $(MLX_NAME) $(BOBJ)
	$(CC) $(BOBJ) $(CFLAGS) $(LFT_FLAG) -o $(NAME)

$(NAME): $(LIBFT_NAME) $(MLX_NAME) $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(LFT_FLAG) -o $(NAME)

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

.PHONY: all clean fclean re bonus
