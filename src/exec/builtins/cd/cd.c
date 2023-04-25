/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthibaul <mthibaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:54:00 by mthibaul          #+#    #+#             */
/*   Updated: 2023/04/17 13:43:57 by mthibaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	args_nb(char **args);
static int	cd_no_arg(t_env *env);
static char	*replace_tilde(t_env *env);

int cd(t_env *env, char **args)
{
	int len;

	len = args_nb(args);
	if (len == 1)
		return (cd_no_arg(env));
	else if (len > 2)
		return (ft_putstr_fd("🛸~> cd: too many arguments\n", STDERR_FILENO), 1);
	if (args[1][0] == '~')
		args[1] = replace_tilde(env);
	if (chdir(args[1]) != 0)
	{
		print_builtin_error("cd", args[1]);
		perror(NULL);
		return (1);
	}
	return (0);
}

static char	*replace_tilde(t_env *env)
{
	char *path;

	while (env)
	{
		if (ft_strcmp(env->name, "HOME") == 0)
		{
			path = env->value;
			return (path);
		}
		env = env->next;
	}
	ft_putstr_fd("🛸~> cd: HOME not set\n", STDERR_FILENO);
	return (NULL);
}

static int cd_no_arg(t_env *env)
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
	return (1);
}

static int args_nb(char **args)
{
	int i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}