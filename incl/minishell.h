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

#ifndef MINISHELL_H
# define MINISHELL_H

/* SYSTEM LIBS */
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>

/* HEADER FILES */
# include "libft.h"

/* PROMPT */
# define PROMPT "🛸~> "
# define SEPARATOR '\1'
# define EMPTY_SPACE '\2'

/* BOOLEAN */
# define TRUE 1
# define FALSE 0

/* COLORS */
# define KNORMAL "\x1B[0m"
# define KRED "\x1B[31m"
# define KGREEN "\x1B[32m"
# define KYELLOW "\x1B[33m"
# define KBLUE "\x1B[34m"
# define KWHITE "\x1B[37m"

/* ERROR CODES */
# define ERR_MALLOC -2

/* ERROR MSG */
# define ERR_MALLOC_MSG "Memory allocation has failed. \x1B[0m\n\x1B[33mPlease make sure enough memory is dedicated to the process.\n"
# define PIPE_ERR_MSG "⛔️: syntax error near unexpected token `|'\n"
# define PIPE_ERR_MSG2 "⛔️: syntax error near unexpected token `||'\n"
# define SINGLEQUOTE_ERR_MSG "⛔️: syntax error near unexpected token `\''\n"
# define DOUBLEQUOTE_ERR_MSG "⛔️: syntax error near unexpected token `\"'\n"
# define REDIRECT_NOEND_ERR_MSG "⛔️: syntax error near unexpected token `newline'\n"
# define REDIRECT_INPUT_ERR_MSG "⛔️: syntax error near unexpected token `<'\n"
# define REDIRECT_OUTPUT_ERR_MSG "⛔️: syntax error near unexpected token `>'\n"
# define REDIRECT_INPUT_ERR_MSG2 "⛔️: syntax error near unexpected token `<<'\n"
# define REDIRECT_OUTPUT_ERR_MSG2 "⛔️: syntax error near unexpected token `>>'\n"

/* CODES */
# define NOT_INIT -1

/* COMMAND TYPES */
# define IS_BUILTIN 55
# define IS_CMD 60

/* REDIRECT CODES */
# define IS_IN -95
# define IS_OUT -96
# define IS_OUT_APPEND -97
# define IS_HEREDOC -98

/* ENVP */
typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}	t_env;

/* LINKED LISTS */
typedef struct s_cmd
{
	int		type;
	char	**content;
	char	**in_out;
	char	*in_out_code;
	void	*next;
}	t_cmd;

/* ERROR CODES PARSING */
# define ERR_ENV_EMPTY_LINE -10000
# define ERR_ENV_EMPTY_REDIRECT -10001
# define ERR_ENV_EMPTY_FULL -10002

typedef struct s_parsing
{
	int		error_code_parsing;
	int		error_code_parsing_saved;
	char	*current_str;
	char	**current_tab;
	char	**current_redirect_tab;
	char	*current_redirect_str;
	char	*current_in_out_code;
	int		quote_end;
}	t_parsing;

typedef struct s_shell
{
	t_parsing	parsing;
	t_cmd		*command;
	char		*input;
	int			last_err_code;
	t_env		*env;
}	t_shell;

/* LINKED LISTS */
t_cmd		*lstcreate(char **content, char **in_out, char *in_out_code);
void		lstadd_back(t_cmd **lst, t_cmd *new);
void 		test(t_shell *shell, char **env);
t_cmd		*lstinit(void);

/* PROMPT */
void		prompt(t_shell *shell);

/* SIGNALS */
# define BEFORE_PROMPT 6555
# define IN_PARSING 6556
# define IN_PROMPT 6559
# define EXECUTION 6557
# define CTRL_C 6558
# define CTRL_SLASH 6560

int		signal_init(t_shell *shell);

/* ENVP */
char		*find_name(char *envp);
char		*find_value(char *envp);
void		free_env(t_env *env);
void		free_env_str(char **env);
char		**env_to_str(t_env *env);
t_env		*envp_to_list(char **envp);
int			envadd_elem(t_env *env, char *name, char *value);
void 		envadd_back(t_env *env, t_env *new);
t_env		*env_create(char *name, char *value);

/* PARSING */
void		parsing(t_shell *shell);
void		split_shell(t_shell *shell);

/* CMD SPLITTING */
void		separators_split(t_shell *shell, size_t *i, int *state);
void		end_found(t_shell *shell, size_t i);
void		empty_args(t_shell *shell, size_t *i, int state);
void		replace_empty_spaces(t_shell *shell);
void		add_separator(t_shell *shell);
void		env_gestion(t_shell *shell, size_t *i, int *state);
void		split_space_env(t_shell *shell, size_t *i, int *state);
int			find_env(t_shell *shell, int *state, char *env_name);
int			empty_env_errors(t_shell *shell, size_t *i, int *state, char *env_name);

/* QUOTE STATE */
# define DOUBLE_QUOTE -15
# define SINGLE_QUOTE -16
# define SPACE_SEP -17
# define REDIRECT -18
# define REDIRECT_SINGLE_QUOTE -19
# define REDIRECT_DOUBLE_QUOTE -20
# define REDIRECT_END -21

/* ENV DETECTION */
char	*env_spaces(char *env);

/* ERROR CHECK */
int			errors(t_shell *shell);
int			pipe_check(t_shell *shell, size_t i, int state);
int			quotes_state_error(t_shell *shell, size_t i, int state);
int			quotes_check(t_shell *shell, size_t i, int state);
int			redirections_check(t_shell *shell, size_t i, int state);

/* EXITS */
void		clean_exit(t_shell *shell);
void		malloc_err_exit(t_shell *shell);
void		debug_print(t_shell *shell);

/* FREE COMMANDS */
void		cmd_free(t_shell *shell);

/* BUILTINS */
void		print_builtin_error(char *builtin, char *arg);
int			echo(char **arg);
int			cd(t_env *env, char **arg);
int			pwd(void);
int			export(t_env *env, char **args);
int			unset(char **args, t_env **env);
int			env_builtin(char **args, t_env *env);
int			exit_builtin(char **args, t_env *env);
int			check_builtins(t_cmd *cmd, t_env *env);

/* UTILS */
int		ft_strcmp(char *str1, char *str2);

#endif
