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
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>

/* HEADER FILES */
# include "libft.h"

/* PROMPT */
# define PROMPT "🛸~> "
# define SEPARATOR '\1'

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
# define MSG_ERR_MALLOC "Allocation has failed.\n Please make sure enough memory is dedicated to the process.\n"

/* CODES */
# define NOT_INIT -1

/* TYPES */
# define IS_BUILTIN 55
# define IS_CMD 60


/* REDIRECT CODES */
# define IS_IN -95
# define IS_OUT -96
# define IS_OUT_APPEND -97
# define IS_HEREDOC -98

/* PIPES */
typedef struct s_pipe
{
	int	cmd_nb;
	int	pipe_nb;
	int	index;
	int	*pipes_tab;
}	t_pipe;

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

typedef struct s_parsing
{
	char	*current_str;
	char	**current_tab;
	char	**current_redirect_tab;
	char	*current_redirect_str;
	char	*current_in_out_code;
}	t_parsing;

typedef struct s_shell
{
	t_parsing	parsing;
	t_cmd		*command;
	char		*input;
	int			last_err_code;
}	t_shell;

/* LINKED LISTS */
t_cmd		*lstcreate(char **content, char **in_out, char *in_out_code);
void		lstadd_back(t_cmd **lst, t_cmd *new);
void 		test(t_shell *shell, char **env);
t_cmd		*lstinit(void);

void	prompt(t_shell *shell);

/* ENVP */
char	*find_name(char *envp);
char	*find_value(char *envp);
void	free_env(t_env *env);
void	free_env_str(char **env);
char	**env_to_str(t_env *env);
t_env	*envp_to_list(char **envp);
int		envadd_elem(t_env *env, char *name, char *value);
void 	envadd_back(t_env *env, t_env *new);
t_env	*env_create(char *name, char *value);

/* PARSING */
void	parsing(t_shell *shell);
void	split_shell(t_shell *shell);

/* CMD SPLITTING */
void	separators_split(t_shell *shell, size_t *i, int *state);
void	end_found(t_shell *shell, size_t i, int state);

/* EXITS */
void	clean_exit(t_shell *shell);
void	malloc_err_exit(t_shell *shell);
void	debug_print(t_shell *shell);

/* COMMANDS */
int		cmd_nb(t_env *env, t_cmd *cmd);
int		exec_cmd(t_cmd *cmd, t_env *env, t_pipe *pipe);

/* PIPES */
int		pipes(t_env *env, t_cmd *cmd, int cmd_nb);
int		pipes_dup(t_pipe *pipe);
void	close_pipes(t_pipe *pipe);


/* BUILTINS */
void	print_builtin_error(char *builtin, char *arg);
int		echo(char **arg);
int		cd(t_env *env, char **arg);
int		pwd(void);
int		export(t_env *env, char **args);
int		unset(char **args, t_env *env);
int		env_builtin(char **args, t_env *env);
int		exit_builtin(char **args, t_env *env);

/* UTILS */
int	ft_strcmp(char *str1, char *str2);

#endif
