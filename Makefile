
SRCS    = main.c ft_free_ptr.c ft_game.c ft_events.c

NAME    = cub3D

LBFT	= libft/libft.a

CC		= cc -g

CFLAGS  = -Wall -Wextra -Werror #-fsanitize=address

MX		= -lmlx -framework OpenGL -framework Appkit

MAKEC	= make clean

MAKEF	= make fclean

OBJS 	= ${SRCS:.c=.o}

all: $(NAME)

$(NAME): ${OBJS}
	@$(MAKE) -C libft
	@$(CC) $(CFLAGS) $(MX) ${LBFT} ${OBJS} -o ${NAME}

clean:
	@$(MAKEC) -C libft
	@${RM} ${OBJS}

fclean: clean
	@$(MAKEF) -C libft
	@${RM} ${NAME}

re: fclean all
	@$(MAKER) -C libft

.PHONY: all clean fclean re
