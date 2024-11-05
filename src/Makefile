# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/02 20:21:52 by AleXwern          #+#    #+#              #
#    Updated: 2024/11/05 21:07:24 by AleXwern         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAG	= -m64 -no-pie -Wall -Wextra -Werror -MMD
SRCFILE	= color.cpp define_set.cpp events.cpp fractol.cpp key_input.cpp main.cpp mou_input.cpp
OBJ		= $(addprefix ./obj/,$(SRCFILE:.cpp=.o))
DEPNS	= $(OBJ:.o=.d)
INCLS	= -I ../includes -I ../Libft/includes -I C:\SDL\SDL2-2.0.12\include
GREEN	= \033[0;32m
PURPLE	= \033[0;35m
STOP	= \033[0m
GCC		= g++

.PHONY: all clean fclean re

all: $(OBJ)

-include $(DEPNS)

./obj/%.o:%.cpp
	@echo "Compiling $(GREEN)$@$(STOP)"
	@mkdir -p obj
	g++ $(FLAG) -c $< -o $@ $(INCLS)
	@cp $@ ../obj

clean:
	@/bin/rm -f $(OBJ)
	@/bin/rm -rf ./obj

fclean: clean
	@/bin/rm -f $(OBJ)
	@/bin/rm -f $(DEPNS)
	@/bin/rm -rf ./obj

re: fclean all
