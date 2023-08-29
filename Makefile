NAME := cub3d

SRC := main.c flood_fill.c grid_ops.c getters.c
OBJ := $(SRC:%.c=%.o)

FT_DIR := ./libft
FT_SRC_DIR := $(FT_DIR)/src
LIBFT_NAME := $(FT_DIR)/build/libft.a
LFT_FLAG := -L$(FT_DIR)/build/ -lft
CC := cc
INCLUDE := -I$(FT_SRC_DIR)
CFLAGS := -Wall -Werror -Wextra -g3 $(INCLUDE)

all: $(NAME)

$(NAME): $(LIBFT_NAME) $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(LFT_FLAG) -o $(NAME)

$(LIBFT_NAME):
	make -C ./libft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C $(FT_DIR)
	/bin/rm -f $(OBJ)

fclean: clean
	make fclean -C $(FT_DIR)
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
