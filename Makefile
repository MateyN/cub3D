GREEN	=	\e[92;5;118m
YELLOW	=	\e[93;5;226m
RESET	=	\e[0m

NAME = cud3d

SRCS_DIR = srcs

SRCS = $(SRCS_DIR)/main.c \
       $(SRCS_DIR)/draw.c \
       $(SRCS_DIR)/ft_errors.c \
       $(SRCS_DIR)/ft_free_ptr.c \
       $(SRCS_DIR)/game.c \
       $(SRCS_DIR)/get_next_line.c \
       $(SRCS_DIR)/get_next_line_utils.c \
       $(SRCS_DIR)/init.c \
       $(SRCS_DIR)/movement.c \
       $(SRCS_DIR)/movement_utils.c \
       $(SRCS_DIR)/parse_line.c \
       $(SRCS_DIR)/parse_line_utils.c \
       $(SRCS_DIR)/parse_map.c \
       $(SRCS_DIR)/parsing.c \
       $(SRCS_DIR)/parsing_utils.c \
       $(SRCS_DIR)/raycasting.c \
       $(SRCS_DIR)/raycasting_utils.c \
       $(SRCS_DIR)/render.c \

OBJS = $(SRCS:%.c=%.o)

MAKEC	= make clean

MAKEF	= make fclean

CC = cc

CFLAGS = -g3 -Wall -Werror -Wextra -fsanitize=address

all:$(NAME)

$(NAME):${OBJS}
	@printf "$(YELLOW) - Compiling $(NAME) ... $(RESET)\n"
	@$(MAKE) -s -C libft
	@$(MAKE) -s -C mlx
	$(CC) $(CFLAGS) $(OBJS) ./libft/libft.a ./mlx/libmlx.a -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)
	@printf "\033[1;32m - cub3D is ready!\033[0m\n"

$(SRCS_DIR)/%.o: $(SRCS_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(MAKEC) -C libft --silent
	@${RM} ${OBJS}

fclean: clean
	@$(MAKEF) -C libft --silent
	@${RM} ${NAME}

re: fclean all
	@$(MAKE) -s -C libft --silent

.PHONY: all clean fclean re