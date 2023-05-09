TO DO:

- movement
- NORM
LIBFT_DIR = ./lib/libft/


SRCS = $(addprefix srcs/, $(SRC))

UNAME= $(shell uname -s)

ifeq ($(UNAME), Linux)
		MLX_DIR = ./lib/minilibx/linux
		MLX_FLAGS = -lmlx_Linux -lX11 -lXext -lm -lz
else
		MLX_DIR = ./lib/minilibx/mac
		MLX_FLAGS = -lmlx -lm -framework OpenGL -framework AppKit
endif

INC = -Iincludes -I$(LIBFT_DIR) -I$(MLX_DIR) 
FLAGS = -Wall -Wextra -Werror
CC = gcc

RM = rm -rf

DIR = file_object
OB = $(addprefix $(DIR)/, $(SRCS:%.c=%.o))
CLONE = file_object \
	file_object/srcs \
	file_object/srcs/manage_error \

$(DIR)/%.o : %.c
	@make -C $(LIBFT_DIR)
	@make -C $(MLX_DIR)
	@mkdir -p $(CLONE)
	@$(CC) $(INC) $(FLAGS) -c $^ -o $@

all : $(NAME)

$(NAME) : $(OB)
	@echo "Compiling cub3d..."
	@$(CC) $(OB) ./lib/libft/libft.a -L$(MLX_DIR) $(MLX_FLAGS) -o $@
	@echo "Compilation [cub3d] is done!"

clean :
	@echo "Remove all file_object..."
	@$(RM) $(DIR)
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(MLX_DIR)
	@echo "file_object removed!"

fclean : clean
	@make fclean -C $(LIBFT_DIR)
	@echo "Remove all file_object & file_binary..."
	@$(RM) $(NAME)
	@echo "object and binary_file removed!"

debug: FLAGS += -g3 -D DEBUG=1
debug: all
asan: FLAGS += -g3 -fsanitize=address
asan: all

re : fclean $(NAME)
.PHONY: all clean fclean re