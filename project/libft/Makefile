# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: damerica <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/03 18:18:48 by damerica          #+#    #+#              #
#    Updated: 2019/09/18 19:56:27 by damerica         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
OBJ = ft_memset.c \
        ft_bzero.c \
        ft_memcpy.c \
        ft_memccpy.c \
        ft_memmove.c \
        ft_memchr.c \
        ft_memcmp.c \
        ft_strlen.c \
        ft_strdup.c \
        ft_strcpy.c \
        ft_strncpy.c \
        ft_strcat.c \
        ft_strncat.c \
        ft_strlcat.c \
        ft_strchr.c \
        ft_strrchr.c \
        ft_strstr.c \
        ft_strnstr.c \
        ft_strcmp.c \
        ft_strncmp.c \
        ft_atoi.c \
        ft_isalpha.c \
        ft_isdigit.c \
        ft_isalnum.c \
        ft_isascii.c \
        ft_isprint.c \
        ft_toupper.c \
        ft_tolower.c \
        ft_memalloc.c \
        ft_memdel.c \
        ft_strnew.c \
        ft_strdel.c \
        ft_strclr.c \
        ft_striter.c \
        ft_striteri.c \
        ft_strmap.c \
        ft_strmapi.c \
        ft_strequ.c \
        ft_strnequ.c \
        ft_strsub.c \
        ft_strjoin.c \
        ft_strtrim.c \
        ft_strsplit.c \
        ft_itoa.c \
        ft_putchar.c \
        ft_putnbr.c \
        ft_putstr.c \
        ft_putendl.c \
        ft_putchar_fd.c \
        ft_putnbr_fd.c \
        ft_putstr_fd.c \
        ft_putendl_fd.c \
        ft_lstnew.c \
        ft_lstdelone.c \
        ft_lstdel.c \
        ft_lstadd.c \
        ft_lstiter.c \
        ft_lstmap.c \
        ft_strrev.c \
        ft_strlowcase.c \
        ft_strupcase.c \
		ft_intlen.c \
		ft_str_is_printable.c \
		ft_strswap.c \
		ft_write_str.c \
		ft_ft_nword.c \
		ft_nwrite_str.c \
                get_next_line.c

OBJ0 = $(OBJ:.c=.o)

all: $(NAME)

$(NAME): $(OBJ0)
	@ar rc $(NAME) $(OBJ0)
	@ranlib $(NAME)
	@echo "\033[0;32mLIBFT COMPILED\033[0m"

%.o:%.c
	gcc -Wall -Wextra -Werror -I ./ -c $< -o $@
clean: 
	@/bin/rm -rf $(OBJ0)

fclean: clean
	@/bin/rm -rf $(NAME)

re: fclean all
