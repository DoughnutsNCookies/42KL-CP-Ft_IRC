# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schuah <schuah@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/08 17:36:21 by plau              #+#    #+#              #
#    Updated: 2024/01/11 20:02:41 by schuah           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	ircserv
DNAME			=	d.out
BOTNAME			=	penguinBot

CXX				=	g++
CXXFLAGS		=	-Wall -Wextra -Werror -Wshadow -std=c++98 -pedantic -MMD -MF ${@:.o=.d}

-include ${OBJ:.o=.d} ${BOT_OBJ:.o=.d}

# DEPFLAGS		=	-MMD -MF ${@:.o=.d}
DFLAGS			=	-fsanitize=address -g3
INCLUDES		=	-Iincs
RM				=	rm -rf
MKDIR			=	mkdir -p
SRC_PATH		=	srcs
OBJ_PATH		=	objs

MAIN			=	${OBJ_PATH}/main.o
HEADERS			=	${shell find incs -type f -name "*.hpp" | grep -v "Bot"}
SRC_PATHS		=	${shell find ${SRC_PATH} -type d | grep -v "Bot"}
OBJ_PATHS		=	${subst ${SRC_PATH}, ${OBJ_PATH}, ${SRC_PATHS}}
SRC				=	${shell find ${SRC_PATH} -type f -name "*.cpp" | grep -v "Bot"}
OBJ				=	${subst ${SRC_PATH}, ${OBJ_PATH}, ${SRC:.cpp=.o}}
OBJ_FILTER		=	${filter-out ${MAIN}, ${OBJ}}

BOT_MAIN		=	${OBJ_PATH}/Bot/main.o
BOT_HEADERS 	= 	${shell find incs/Bot -type f -name "*.hpp"}
BOT_SRC_PATHS	=	${shell find ${SRC_PATH}/Bot -type d}
BOT_OBJ_PATHS	=	${subst ${SRC_PATH}/Bot, ${OBJ_PATH}/Bot, ${BOT_SRC_PATHS}}
BOT_SRC			=	${shell find ${SRC_PATH}/Bot -type f -name "*.cpp"}
BOT_OBJ 		=	${subst ${SRC_PATH}/Bot, ${OBJ_PATH}/Bot, ${BOT_SRC:.cpp=.o}}
BOT_OBJ_FILTER	=	${filter-out ${BOT_MAIN}, ${BOT_OBJ}}

all: 
	${MKDIR} ${OBJ_PATHS}
	make -j ${NAME} penguin

db:
	${RM} ${DNAME}
	make -j ${DNAME}

penguin:
	${MKDIR} ${BOT_OBJ_PATHS}
	make -j ${BOTNAME}

${NAME}: ${OBJ}
	${CXX} ${CXXFLAGS} ${INCLUDES}  -o ${NAME} ${OBJ_FILTER} ${MAIN}

${DNAME}:
	${CXX} ${CXXFLAGS} ${DFLAGS} ${SRC} ${INCLUDES} -o ${DNAME}

${BOTNAME}: ${BOT_OBJ}
	${CXX} ${CXXFLAGS} ${INCLUDES} -o ${BOTNAME} ${BOT_OBJ_FILTER} ${OBJ_FILTER} ${BOT_MAIN} 

${OBJ_PATH}/%.o: ${SRC_PATH}/%.cpp ${HEADERS}
	${CXX} ${CXXFLAGS} ${INCLUDES} -c $< -o $@

${BOT_OBJ_PATHS}/%.o: ${BOT_SRC_PATHS}/%.cpp ${BOT_HEADERS}
	${CXX} ${CXXFLAGS} ${INCLUDES} -c $< -o $@

test: fclean all
	./${NAME}

clean:
	${RM} ${OBJ_PATH} ${BOT_OBJ_PATH}

fclean: clean
	${RM} ${NAME} ${DNAME} ${BOTNAME}

re: fclean all

.PHONY = all clean fclean re db test bot
