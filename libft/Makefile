SRC = ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_memchr.c ft_memcmp.c ft_strlen.c ft_isalpha.c ft_isdigit.c ft_isalnum.c \
	ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_strlcpy.c ft_strlcat.c ft_strnstr.c \
	ft_atoi.c ft_calloc.c ft_strdup.c ft_strstr.c ft_strcmp.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_putchar.c ft_putchar_fd.c ft_putstr_fd.c \
	ft_putendl_fd.c ft_putnbr_fd.c ft_striteri.c ft_strncpy.c

NAME = libft.a

all: $(NAME)

.c.o: 
	gcc -Wall -Wextra -Werror -c $< -o ${<:.c=.o}

OBJS = ${SRC:.c=.o}

$(NAME):	${OBJS}
			ar rcs ${NAME} ${OBJS}
			$(MAKE) -C ft_printf
			ar rcs $(NAME) ft_printf/*.o

clean:
			rm -f ${OBJS}
			$(MAKE) -C ft_printf clean
			
fclean:		clean
			rm -f ${NAME}
			$(MAKE) -C ft_printf fclean

re:			fclean all

.PHONY: all clean fclean re