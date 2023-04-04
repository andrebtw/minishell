# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/30 16:58:58 by anrodri2          #+#    #+#              #
#    Updated: 2023/03/15 00:38:24 by anrodri2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### FINAL COMPILATION FILE ###
NAME = minishell

#### DIRECTORIES ####
SRC_DIR = src/

OBJS_DIR = .objs/

INC_DIR = incl/

LIB_DIR = lib/

#### SOURCE FILES ####
LIBFT = $(LIB_DIR)libft.a

SRCS =	main.c \
		prompt/prompt.c \
		parsing/parsing.c \
		clean_exit/clean_exit.c \
		builtins/exit.c \
		parsing/cmd_split/split_shell.c \
		linked_lists/lstcreate.c \
		test.c
		
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

DEPS = $(OBJS:.o=.d)

#### SYSTEM ####
CC = cc

RM = rm -rf

CFLAGS = -Wall -Werror -Wextra

DFLAGS = -MMD -MP

LFLAGS = -L $(LIB_DIR) -lft -lreadline

IFLAGS = -I $(INC_DIR) -I $(LIB_DIR)

#### RULES ####
all:		$(NAME)

-include	$(DEPS)

$(NAME):	$(LIBFT) $(OBJS)
			$(CC) $(OBJS) $(CFLAGS) $(LFLAGS) -o $@

$(LIBFT):	FORCE
			$(MAKE) all -j -C $(LIB_DIR)

FORCE:

$(OBJS_DIR)%.o:		$(SRC_DIR)%.c
					mkdir -p $(shell dirname @)
					$(CC) $(CFLAGS) $(DFLAGS) $(IFLAGS) -c $< -o $@

clean:
			$(MAKE) clean -C $(LIB_DIR)
			$(RM) $(OBJS_DIR) $(DEPS)

fclean:		clean
			$(RM) $(NAME)

re:	fclean $(NAME)

.PHONY: $(NAME) all clean fclean re FORCE
