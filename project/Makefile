# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bdebbie <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/23 13:43:52 by bdebbie           #+#    #+#              #
#    Updated: 2020/09/24 13:13:09 by bdebbie          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIB = libft/
NAME = asm
CFLAGS = -Wall -Wextra -Werror
CC = gcc
SRC_DIR = src/

SRCS =	    check.c \
	    count.c \
	    find_label.c \
	    free_init.c \
	    is_comment.c \
	    main.c \
	    write_bin.c \
	    get_values.c \
	    is_label.c \
	    switch_args.c \
	    write_n_byte.c \
	    is_command.c \
	    is_name.c \
	    valid.c

OBJ_DIR = obj/

OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

HEADER = -I includes/ -I libft/

ASM_HEADERS_LIST = \
		    op.h\
		    asm.h\
		    asm_op.h\

ASM_HEADERS = $(addprefix ./includes/, $(ASM_HEADERS_LIST))

all: lib $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS) $(LIB)libft.a
	@gcc $(CFLAGS) $(OBJS) $(HEADER) -L $(LIB) -lft -o $(NAME)
	@echo "\033[32mASM COMPILED\033[0m"

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
