/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:54:00 by mthibaul          #+#    #+#             */
/*   Updated: 2023/07/25 16:12:52 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	args_nb(char **args);
static int	cd_no_arg(t_env *env);
static char	*replace_tilde(t_env *env);
char		*cd_save_pwd(t_shell *shell);
void		old_pwd_save(t_env **env, char *pwd_saved);
void		update_pwd(t_env *env, t_shell *shell);

int	cd(t_env *env, char **args, t_shell *shell)
{
	int		len;
	char	*pwd_saved;

	(void)shell;
	pwd_saved = cd_save_pwd(shell);
	if (!pwd_saved)
		cd_no_arg(env);
	len = args_nb(args);
	if (len == 1)
		return (free(pwd_saved), cd_no_arg(env));
	else if (len > 2)
		return (free(pwd_saved), ft_putstr_fd(\
		"cd: too many arguments\n", STDERR_FILENO), 1);
	if (args[1][0] == '~')
	{
		free(args[1]);
		args[1] = replace_tilde(env);
		if (!args[1])
			return (free(pwd_saved), malloc_err_exit(shell), 0);
	}
	if (args[1] && chdir(args[1]) != 0)
		return (print_builtin_error("cd", args[1]), \
		perror(NULL), free(pwd_saved), 1);
	return (old_pwd_save(&env, pwd_saved), update_pwd(env, shell), 0);
}

static char	*replace_tilde(t_env *env)
{
	char	*path;

	while (env)
	{
		if (ft_strcmp(env->name, "HOME") == 0)
		{
			path = ft_strdup(env->value);
			return (path);
		}
		env = env->next;
	}
	ft_putstr_fd("🛸~> cd: HOME not set\n", STDERR_FILENO);
	return (NULL);
}

static int	cd_no_arg(t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->name, "HOME") == 0)
		{
			if (chdir(env->value) != 0)
			{
				print_builtin_error("cd", "HOME not set");
				perror(NULL);
				return (1);
			}
			return (0);
		}
		env = env->next;
	}
	ft_putstr_fd("🛸~> cd: HOME not set\n", STDERR_FILENO);
	return (1);
}

static int	args_nb(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}
