# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: damerica <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/25 16:20:05 by damerica          #+#    #+#              #
#    Updated: 2020/09/25 16:29:53 by damerica         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


LIB = libft/
NAME = disasm
CFLAGS = -Wall -Wextra -Werror
CC = gcc
SRC_DIR = src/

SRCS =	    check_and_find.c \
		main.c \
		disasm.c \
		write.c
OBJ_DIR = obj/

OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

HEADER = -I includes/ -I libft/

ASM_HEADERS_LIST = \
		    asm.h\
		    asm2.h\

ASM_HEADERS = $(addprefix ./includes/, $(ASM_HEADERS_LIST))

all: lib $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS) $(LIB)libft.a
	@gcc $(CFLAGS) $(OBJS) $(HEADER) -L $(LIB) -lft -o $(NAME)
	@echo "\033[32mDISASM COMPILED\033[0m"

lib:
	@make -C $(LIB)

$(OBJ_DIR):
	@mkdir -p obj

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	gcc $(CFLAGS) $(HEADER) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIB) clean

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIB) fclean

re: fclean all

.PHONY: all clean fclean re
