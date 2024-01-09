# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schuah <schuah@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/08 17:36:21 by plau              #+#    #+#              #
#    Updated: 2024/01/09 13:55:36 by schuah           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	ircserv
CXX			=	g++
CXXFLAGS	=	-Wall -Wextra -Werror -Wshadow -std=c++98 -pedantic
DNAME		=	d.out
DFLAGS		=	-fsanitize=address -g3
INCLUDES	=	-Iincs
RM			=	rm -rf
MKDIR		=	mkdir -p
HEADERS		=	${shell find incs -type f -name "*.hpp"}
SRC_PATH	=	srcs
OBJ_PATH	=	objs
MAIN		=	srcs/main.cpp
SRC_PATHS	=	${shell find ${SRC_PATH} -type d}
OBJ_PATHS	=	${subst $(SRC_PATH), $(OBJ_PATH), ${SRC_PATHS}}
SRC			=	${shell find ${SRC_PATH} -type f -name "*.cpp"}
OBJ			=	${subst $(SRC_PATH), $(OBJ_PATH),  ${SRC:.cpp=.o}}

all: 
	${MKDIR} ${OBJ_PATHS}
	make ${NAME} penguin

db:
	${RM} ${DNAME}
	make ${DNAME}

penguin:
	${MKDIR} ${BOT_OBJ_PATHS}
	make ${BOTNAME}

${NAME}: ${OBJ}
	${CXX} ${CXXFLAGS} ${INCLUDES} ${OBJ} -o ${NAME}

${DNAME}:
	${CXX} ${CXXFLAGS} ${DFLAGS} ${SRC} ${INCLUDES} -o ${DNAME}

${BOTNAME}: ${BOT_OBJ}
	${CXX} ${CXXFLAGS} ${BOT_INCLUDES} ${BOT_OBJ} -o ${BOTNAME}

${OBJ_PATH}/%.o: ${SRC_PATH}/%.cpp ${HEADERS}
	${CXX} ${CXXFLAGS} ${INCLUDES} -c $< -o $@

${BOT_OBJ_PATHS}/%.o: ${BOT_SRC_PATHS}/%.cpp ${BOT_HEADERS}
	${CXX} ${CXXFLAGS} ${BOT_INCLUDES} -c $< -o $@

test: fclean all
	./${NAME}

clean:
	${RM} ${OBJ_PATH} ${BOT_OBJ_PATHS}

fclean: clean
	${RM} ${NAME} ${DNAME} ${BOTNAME}

re: fclean all

.PHONY = all clean fclean re db test bot
