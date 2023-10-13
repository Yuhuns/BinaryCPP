# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: awallet <awallet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/08 17:29:53 by awallet           #+#    #+#              #
#    Updated: 2023/10/12 20:10:54 by awallet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = binary

CC = c++ -std=c++98
CFLAGS = -pedantic -Wall -Wextra -Werror -I./includes -MMD -MP -fsanitize=address

SRC =  $(shell find . -name "*.cpp")
OBJ = $(SRC:.cpp=.o)
DEP	= $(OBJ:.o=.d)

%.o : %.cpp
		${CC} ${CFLAGS} -c $< -o $@

all:    ${NAME}

${NAME}:${OBJ}
		${CC} ${CFLAGS} ${OBJ} -o ${NAME}

clean:
	@find . -name "*.o" -delete
	@find . -name "*.d" -delete
	@find . -name "*_shrubbery" -delete
	@echo "Cleaning"

fclean: clean
	@if [ -f ${NAME} ]; then rm ${NAME}; fi
	@echo "Done"

re: fclean all

#Dependencies list
-include ${DEP}

.PHONY: all clean fclean re