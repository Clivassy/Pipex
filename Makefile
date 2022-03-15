NAME = pipex

SRCS = pipex.c ft_utils.c ft_split.c ft_parsing.c ft_strjoin.c

OBJS = ${SRCS:.c=.o}

CC = gcc
CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

all: ${NAME} pipex.h
${NAME}: ${OBJS}
	@${CC} ${CFLAGS} ${OBJS} -o pipex

clean: 
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
