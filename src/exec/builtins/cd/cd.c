/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthibaul <mthibaul@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:54:00 by mthibaul          #+#    #+#             */
/*   Updated: 2023/04/04 15:54:00 by mthibaul         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	args_nb(char **args);
static int	cd_no_arg(t_env *env);
static char	*replace_tilde(char **args, t_env *env);

int cd(char **args, t_env *env)
{
	int len;

	len = args_nb(args);
	if (len == 1)
		return (cd_no_arg(env));
	else if (len > 2)
		return (ft_putstr_fd("\uD83D\uDEF8~> cd: too many arguments\n", STDERR_FILENO), 1);
	if (args[1][0] == '~')
		args[1] = replace_tilde(args, env);
	if (!chdir(args[1]))
	{
		/* print_error */
		return (1);
	}
}

static char	*replace_tilde(char **args, t_env *env)
{
	char *path;

	while (ft_strcmp(env->name, "HOME") != 0)
		env = env->next;
	path = ft_strjoin(env->value, args[1]);
	return (path);
}

static int cd_no_arg(t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->name, "HOME") == 0)
		{
			if (!chdir(env->value))
			{
				/* print_error */
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