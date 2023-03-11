/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:19:27 by anrodri2          #+#    #+#             */
/*   Updated: 2023/03/11 18:37:24 by anrodri2         ###   ########.fr       */
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
# define MSG_ERR_MALLOC "%sAllocation has failed.\n Please make sure enough memory is dedicated to the process.\n%s"

/* CODES */
# define NOT_INIT -1

/* LINKED LISTS */
typedef struct s_cmd
{
	int		is_builtin;
	int		is_cmd;
	int		is_pipe;
	int		is_redirect;
	void	*next;
}	t_cmd;

typedef struct s_shell
{
	t_cmd	command;
	char	*input;
	char	**tab;
	int		last_err_code;
}	t_shell;

/* PROMPT */
# define PROMPT "🛸~> "

void	prompt(t_shell *shell);

/* PARSING */
void	parsing(t_shell *shell);

/* EXITS */
void	clean_exit(t_shell *shell);
void	malloc_err_exit(t_shell *shell);

/* BUILTINS */
void	bi_exit(t_shell *shell);

#endif
