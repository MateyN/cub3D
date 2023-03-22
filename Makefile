GREEN		=	\e[92;5;118m
YELLOW		=	\e[93;5;226m
RESET		=	\e[0m

NAME    = cub3D 

LBFT	= libft/libft.a

CC		= cc -g

CFLAGS  = -Wall -Wextra -Werror #-fsanitize=address

MLX		= -lmlx -framework OpenGL -framework Appkit

MAKEC	= make clean

MAKEF	= make fclean

SRCS	= $(wildcard srcs/*.c)

OBJS 	= ${SRCS:.c=.o}

INCS	= $(wildcard includes/*.h)

all: $(NAME)

$(NAME): ${OBJS}
	@printf "$(YELLOW) 	- Compiling $(NAME)... $(RESET)\n"
	@$(MAKE) -s -C libft --silent
	@$(CC) $(CFLAGS) $(MLX) ${LBFT} ${OBJS} main.c -o ${NAME}
	@printf "$(_SUCCESS) $(GREEN)       - $(NAME) is ready!\n$(RESET)"

%.o: %.c $(INCS)
	@$(CC) $(CFLAGS) -c $< -o $@ -I includes/

clean:
	@$(MAKEC) -C libft --silent
	@${RM} ${OBJS}

fclean: clean
	@$(MAKEF) -C libft --silent
	@${RM} ${NAME}

re: fclean all
	@$(MAKE) -s -C libft --silent

.PHONY: all clean fclean re
