NAME = philo

SRCS = \
	args_validation.c \
	main.c \
	monitoring.c \
	philo_utils.c \
	 philo_routine.c \

OBJS = ${SRCS:.c=.o}

CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g

all: ${NAME}
%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME} -pthread



clean:
	${RM} ${OBJS} 

fclean: clean
	${RM} ${NAME}

re: fclean all

