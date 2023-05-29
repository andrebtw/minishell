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
		parsing/cmd_split/split_shell.c \
		parsing/cmd_split/split_shell_state.c \
		parsing/cmd_split/split_shell_utils1.c \
		parsing/cmd_split/split_shell_utils2.c \
		parsing/cmd_split/empty_args.c \
		parsing/cmd_split/env_gestion.c \
		parsing/cmd_split/env_gestion2.c \
		parsing/cmd_split/env_spaces.c \
		parsing/errors/errors.c \
		parsing/errors/pipes.c \
		parsing/errors/quotes_check.c \
		parsing/errors/redirections.c \
		parsing/errors/redirections2.c \
		parsing/cmd_free/cmd_free.c \
		linked_lists/lstcreate.c \
		test.c \
		envp/envp_to_list/envp_to_list.c \
		envp/envp_to_list/find_list_content.c \
		envp/envp_to_list/free_env.c \
		envp/env_to_str/env_to_str.c \
		exec/exec.c \
		exec/builtins/exit/exit.c \
		exec/exec_utils.c \
		exec/builtins/print_builtin_error.c \
		exec/builtins/echo/echo.c \
		exec/builtins/cd/cd.c \
		exec/builtins/pwd/pwd.c \
		exec/builtins/export/export.c \
		exec/builtins/unset/unset.c \
		exec/builtins/env/env_builtin.c \
		debug_print.c \


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
