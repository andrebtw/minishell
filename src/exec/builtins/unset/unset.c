/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:32:00 by mthibaul          #+#    #+#             */
/*   Updated: 2023/07/25 13:52:55 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_code;
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

	(void)shell;
	i = 0;
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
	{
		print_builtin_error("unset", arg);
		ft_putstr_fd("not a valid identifier\n", STDERR_FILENO);
		g_code = 1;
		return (1);
	}
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			print_builtin_error("unset", arg);
			ft_putstr_fd("not a valid identifier\n", STDERR_FILENO);
			g_code = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

int	envdel_elem2(t_env **env)
{
	t_env	*tmp;

	tmp = (*env)->next;
	if (!tmp)
	{
		free((*env)->name);
		free((*env)->value);
		free(*env);
		return (TRUE);
	}
	(*env)->name = ft_strdup(tmp->name);
	(*env)->value = ft_strdup(tmp->value);
	(*env)->next = tmp->next;
	free(tmp->name);
	free(tmp->value);
	free(tmp);
	return (TRUE);
}

void	envdel_elem(char *arg, t_env *env)
{
	t_env	*tmp;


	if (env && ft_strcmp(arg, env->name) == 0)
	{
		if (!env->next)
		{
			free(env->name);
			free(env->value);
			env->name = NULL;
			return ;
		}
		else if (envdel_elem2(&env))
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
