# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: AleXwern <AleXwern@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/01 10:42:05 by alexwern          #+#    #+#              #
#    Updated: 2024/11/11 19:46:35 by AleXwern         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= fractol.exe
FLAG	= -m64 -Wall -Wextra -Werror -std=c++17
SRCFILE	= color.cpp define_set.cpp events.cpp fractol.cpp main.cpp
OBJ		= $(addprefix ./obj/,$(SRCFILE:.cpp=.o))
LIBFT	= ./SDL3.lib
INCLS	= -I ./includes
GREEN	= \033[0;32m
PURPLE	= \033[0;35m
STOP	= \033[0m
TEMP0	= 0

.PHONY: all clean fclean re

all: $(NAME)

./build/%.exe:./obj/%.o
	@echo "Compiling $(GREEN)$@$(STOP)"
	g++ $(FLAG) -o $@ $(INCLS) $< $(addprefix $(subst obj/,,$(subst _test.o,,$<))/,$(subst _test,,$<)) $(CATCH) $(LIBFT)

sources:
	@make -C src

folders:
	@mkdir -p build
	@mkdir -p obj

$(NAME): folders sources $(OBJ)
	g++ -o $(NAME) ./obj/* $(LIBFT)

clean:
	@make -C src clean
	@/bin/rm -f $(OBJ)
	@/bin/rm -rf ./obj

fclean: clean
	@rm -rf $(NAME)
	@make -C src fclean
	@rm -rf ./build

re: fclean all
