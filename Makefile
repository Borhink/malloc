# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/24 10:30:43 by qhonore           #+#    #+#              #
#    Updated: 2017/10/21 13:57:33 by qhonore          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
 HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./include/ ./libft/include/
LIB_PATH = ./libft/

SRC_NAME = malloc.c init.c
OBJ_NAME = $(SRC_NAME:.c=.o)
LIB_NAME = -lft
NAME = libft_malloc_$(HOSTTYPE).so
DEP = include/malloc.h

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))
LIB = $(addprefix -L,$(LIB_PATH))

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: lib
	@echo "\033[32;44m Make $(NAME) \033[0m"
	@make $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -shared -o $@ $^
	ln -sf $(NAME) libft_malloc.so

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(DEP)
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

lib:
	@make -C ./libft/

clean:
	rm -rf $(OBJ) $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)
	rm -f libft_malloc.so
	@make -C ./libft/ fclean

re: fclean all

test: $(NAME)
	gcc main.c -I./include/ -I./libft/include/ libft_malloc.so
	/usr/bin/time -l ./a.out

.PHONY: lib clean fclean re
