SRC = init.c philo_utils.c philo.c philo_utils2.c philo_utils3.c

NAME = philo
FLAGS = -Wextra -Werror -Wall -pthread
OBJS = ${SRC:.c=.o}

all : ${NAME}

${OBJS} : %.o:%.c
		cc ${FLAGS} -c $< -o $@

${NAME} : ${OBJS}
		cc ${FLAGS} ${OBJS} -o ${NAME}

clean :
		rm -f ${OBJS}

fclean : clean
		rm -f ${NAME}

re :	fclean all

.PHONY : all clean  fclean 