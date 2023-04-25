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
#### DIRECTORIES ####
SRC_DIR = src

OBJS = $(SRCS:.c=.o)
HEADER = $(SRC_DIR)/header.h


#### SOURCE FILES ####
SRCS =	$(SRC_DIR)/main.c \
		$(SRC_DIR)/prompt/prompt.c \
		$(SRC_DIR)/parsing/parsing.c \
		$(SRC_DIR)/clean_exit/clean_exit.c \
		$(SRC_DIR)/builtins/exit.c \
		$(SRC_DIR)/parsing/cmd_split/split_shell.c \
		$(SRC_DIR)/parsing/cmd_split/split_shell_utils1.c \
		$(SRC_DIR)/linked_lists/lstcreate.c \
		$(SRC_DIR)/test.c \
		$(SRC_DIR)/debug_print.c
		parsing/parsing.c \
		clean_exit/clean_exit.c \
		parsing/cmd_split/split_shell.c \
		linked_lists/lstcreate.c \
		test.c \
		envp/envp_to_list/envp_to_list.c \
		envp/envp_to_list/find_list_content.c \
		envp/envp_to_list/free_env.c \
		envp/env_to_str/env_to_str.c \
		exec/exec.c \
		exec/exec_utils.c \
		exec/builtins/print_builtin_error.c \
		exec/builtins/echo/echo.c \
		exec/builtins/cd/cd.c \
		exec/builtins/pwd/pwd.c \
		exec/builtins/export/export.c \
		exec/builtins/unset/unset.c \
		exec/builtins/env/env_builtin.c \
		exec/builtins/exit/exit.c \
		
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

DEPS = $(OBJS:.o=.d)

#### SYSTEM ####
CC = cc

RM = rm -rf

CFLAGS = -Wall -Werror -Wextra -g3

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
					mkdir -p $(shell dirname $@)
					$(CC) $(CFLAGS) $(DFLAGS) $(IFLAGS) -c $< -o $@

clean:
			$(MAKE) clean -C $(LIB_DIR)
			$(RM) $(OBJS_DIR) $(DEPS)

fclean:		clean
			$(RM) $(NAME)

re:	fclean $(NAME)

.PHONY: all clean fclean re FORCE
