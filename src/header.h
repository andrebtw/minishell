/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:19:27 by anrodri2          #+#    #+#             */
/*   Updated: 2023/03/17 22:41:07 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

/* SYSTEM LIBS */
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

/* HEADER FILES */
# include "../lib/libft.h"

/* PROMPT */
# define PROMPT "🛸~> "

/* COLORS */
# define KNORMAL "\x1B[0m"
# define KRED "\x1B[31m"
# define KGREEN "\x1B[32m"
# define KYELLOW "\x1B[33m"
# define KBLUE "\x1B[34m"
# define KWHITE "\x1B[37m"

/* ERROR MESSAGES */

/* ERROR CODES */
# define ERR_MALLOC -2

/* ERROR MSG */
# define MSG_ERR_MALLOC "Allocation has failed.\n Please make sure enough memory is dedicated to the process.\n"

/* CODES */
# define NOT_INIT -1

/* LINKED LISTS */
typedef struct s_cmd
{
	int		type;
	char	**content;
	void	*next;
}	t_cmd;

# define IS_BUILTIN 55
# define IS_CMD 60
# define IS_PIPE 65
# define IS_REDIRECT 70
# define IS_HERE_DOC 75

typedef struct s_parsing
{
	char	*current_str;
	char	**current_tab;
}	t_parsing;

typedef struct s_shell
{
	t_parsing	parsing;
	t_cmd		*command;
	char		*input;
	int			last_err_code;
}	t_shell;

/* LINKED LISTS */
t_cmd		*lstcreate(int type, char **content);
void		lstadd_back(t_cmd **lst, t_cmd *new);
void 		test(t_shell *shell);
t_cmd		*lstinit(void);

void	prompt(t_shell *shell);

/* PARSING */
void	parsing(t_shell *shell);
void	split_shell(t_shell *shell);

/* EXITS */
void	clean_exit(t_shell *shell);
void	malloc_err_exit(t_shell *shell);
void	debug_print(t_shell *shell);

/* BUILTINS */
void	bi_exit(t_shell *shell);

#endif
