NAME = philo

SRC = main.c philos.c routine.c get_n_set.c utils.c monitor.c parsing.c print.c

OBJS = ${SRC:.c=.o}

RM = rm -f

CC = cc

CFLAGS = -pthread -Wall -Wextra -Werror -g

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			${CC} ${CFLAGS} -o ${NAME} ${OBJS}

all: ${NAME}

clean: 
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY:	all clean fclean re

