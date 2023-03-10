# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anrodri2 <anrodri2@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/30 16:58:58 by anrodri2          #+#    #+#              #
#    Updated: 2023/03/10 12:19:12 by anrodri2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#### SYSTEM ####
CC = cc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra

#### DIRECTORIES ####
SRC_DIR = src

#### SOURCE FILES ####
SRCS =	$(SRC_DIR)/main.c
OBJS = $(SRCS:.c=.o)
HEADER = $(SRC_DIR)/header.h

### FINAL COMPILATION FILE ###
NAME = minishell

### LIBFT ###
LIBFT = lib/libft.a

#### RULES ####
all:		$(NAME)

$(NAME):	libft_comp $(OBJS) $(HEADER)
			$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -Llib -lft

%.o: %.c	$(HEADER) Makefile
			$(CC) $(CFLAGS) -c $< -o $@

clean:
			@$(MAKE) clean -C lib
			$(RM) $(OBJS)

fclean:
			@$(MAKE) fclean -C lib
			$(RM) $(OBJS) $(NAME)

libft_comp:
			@$(MAKE) all -j -C lib

re:	fclean $(NAME)

.PHONY: all clean fclean re