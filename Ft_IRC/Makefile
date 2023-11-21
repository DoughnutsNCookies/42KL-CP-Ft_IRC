# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schuah <schuah@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/08 17:36:21 by plau              #+#    #+#              #
#    Updated: 2023/11/17 21:16:56 by schuah           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	ircserv
CXX				=	g++
CXXFLAGS	=	-Wall -Wextra -Werror -Wshadow -std=c++98 -pedantic
DNAME			=	d.out
DFLAGS		=	-fsanitize=address -g3
INCLUDES	=	-Iincs
RM				=	rm -rf
MKDIR			=	mkdir -p
HEADERS		=	${shell find incs -type f -name "*.hpp"}
SRC_PATH	=	srcs
OBJ_PATH	=	objs
MAIN			=	srcs/main.cpp
SRC_PATHS	=	${shell find ${SRC_PATH} -type d}
OBJ_PATHS	=	${subst $(SRC_PATH), $(OBJ_PATH), ${SRC_PATHS}}
SRC				=	${shell find ${SRC_PATH} -type f -name "*.cpp"}
OBJ				=	${subst $(SRC_PATH), $(OBJ_PATH),  ${SRC:.cpp=.o}}

all: 
	${MKDIR} ${OBJ_PATHS}
	make ${NAME}

db: $(DNAME)

${NAME}: ${OBJ}
	${CXX} ${CXXFLAGS} ${INCLUDES} ${OBJ} -o ${NAME}

${DNAME}:
	${CXX} ${CXXFLAGS} $(DFLAGS) ${SRC} ${INCLUDES} -o ${DNAME}

${OBJ_PATH}/%.o: ${SRC_PATH}/%.cpp ${HEADERS}
	${CXX} ${CXXFLAGS} ${INCLUDES} -c $< -o $@

test: fclean all
	./${NAME}

clean:
	${RM} ${OBJ_PATH}

fclean: clean
	${RM} ${NAME} ${DNAME}

re: fclean all

.PHONY = all clean fclean re db test