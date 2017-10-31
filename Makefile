# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qhonore <qhonore@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/24 10:30:43 by qhonore           #+#    #+#              #
#    Updated: 2017/10/29 13:53:48 by qhonore          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
 HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./include/

SRC_NAME = malloc.c init.c utils.c show_alloc_mem.c free.c libft.c realloc.c
OBJ_NAME = $(SRC_NAME:.c=.o)
NAME = libft_malloc_$(HOSTTYPE).so
DEP = include/malloc.h

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))

CC = gcc -g
CFLAGS = -Wall -Wextra -Werror

all:
	@echo "\033[32;44m Make $(NAME) \033[0m"
	@make $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -shared -o $@ $^
	ln -sf $(NAME) libft_malloc.so

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(DEP)
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	rm -rf $(OBJ) $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)
	rm -f libft_malloc.so

re: fclean all

test: $(NAME)
	gcc main.c -I./include/ libft_malloc.so
	/usr/bin/time -l ./a.out

.PHONY: lib clean fclean re
