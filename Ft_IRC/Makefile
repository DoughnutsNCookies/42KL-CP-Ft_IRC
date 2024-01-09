# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schuah <schuah@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/08 17:36:21 by plau              #+#    #+#              #
#    Updated: 2024/01/09 14:05:40 by schuah           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	ircserv
DNAME			=	d.out
BOTNAME			=	penguinBot

CXX				=	g++
CXXFLAGS		=	-Wall -Wextra -Werror -Wshadow -std=c++98 -pedantic
DFLAGS			=	-fsanitize=address -g3
INCLUDES		=	-Iincs
BOT_INCLUDES	= 	-Ibot/incs
RM				=	rm -rf
MKDIR			=	mkdir -p

HEADERS			=	${shell find incs -type f -name "*.hpp"}
BOT_HEADERS 	= 	${shell find bot/incs -type f -name "*.hpp"}
SRC_PATH		=	srcs
OBJ_PATH		=	objs
BOT_PATH		=	bot
BOT_SRC_PATH	=	${BOT_PATH}/${SRC_PATH}
BOT_OBJ_PATH	=	${BOT_PATH}/${OBJ_PATH}
SRC_PATHS		=	${shell find ${SRC_PATH} -type d}
BOT_SRC_PATHS	=	${shell find ${BOT_SRC_PATH} -type d}
OBJ_PATHS		=	${subst ${SRC_PATH}, ${OBJ_PATH}, ${SRC_PATHS}}
BOT_OBJ_PATHS	=	${subst ${BOT_SRC_PATH}, ${BOT_OBJ_PATH}, ${BOT_SRC_PATHS}}
SRC				=	${shell find ${SRC_PATH} -type f -name "*.cpp"}
BOT_SRC			=	${shell find ${BOT_SRC_PATH} -type f -name "*.cpp"}
OBJ				=	${subst ${SRC_PATH}, ${OBJ_PATH}, ${SRC:.cpp=.o}}
BOT_OBJ			=	${subst ${BOT_SRC_PATH}, ${BOT_OBJ_PATH}, ${BOT_SRC:.cpp=.o}}

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
