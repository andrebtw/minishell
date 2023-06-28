/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthibaul <mthibaul@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:32:00 by mthibaul          #+#    #+#             */
/*   Updated: 2023/04/12 17:32:00 by mthibaul         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	check_arg(char *arg, t_shell *shell);
static void	envdel_elem(char *arg, t_env *env);

int	unset(char **args, t_env *env, t_shell *shell)
{
	while (*args)
	{
		if (check_arg(*args, shell) == 0)
			envdel_elem(*args, env);
		args++;
	}
	return (0);
}

static int	check_arg(char *arg, t_shell *shell)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
	{
		print_builtin_error("unset", arg);
		ft_putstr_fd("not a valid identifier\n", STDERR_FILENO);
		shell->last_err_code = 1;
		return (1);
	}
	while(arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			print_builtin_error("unset", arg);
			ft_putstr_fd("not a valid identifier\n", STDERR_FILENO);
			shell->last_err_code = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

void	envdel_elem(char *arg, t_env *env)
{
	t_env	*tmp;

	if (env && ft_strcmp(arg, env->name) == 0)
	{
		env->name = NULL;
		env->value = NULL;
		return ;
	}
	while (env && ft_strcmp(arg, env->name) != 0)
	{
		tmp = env;
		env = env->next;
	}
	if (env)
	{
		tmp->next = env->next;
		free(env->name);
		free(env->value);
		free(env);
	}
}
