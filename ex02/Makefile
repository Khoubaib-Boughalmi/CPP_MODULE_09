NAME=PmergeMe
CC= c++
CFLAGS= -Wall -Wextra -Werror

SRCS =	main.cpp \
		parse.cpp \
		sortVector.cpp \
		sortList.cpp \
		PmergeMe.cpp

%.o:%.cpp
	${CC} ${CFLAGS} -c $^ -o $@

OBJS = ${SRCS:.cpp=.o}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}

all: ${NAME}

clean:
	rm -rf ${OBJS}

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re