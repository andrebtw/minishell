/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:04:00 by mthibaul          #+#    #+#             */
/*   Updated: 2023/07/24 17:08:13 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_arg(char *arg, t_env *env);
static int	print_export(t_env *env);
static int	already_exists(char *name, char*value, t_env *env);
int			check_arg2(char *arg, t_env *env, int i);

int	export(t_env *env, char **arg)
{
	int	ret_value;

	ret_value = 0;
	if (!arg[1])
		return (print_export(env));
	arg++;
	while (*arg)
	{
		if (check_arg(*arg, env) != 0)
			ret_value = 1;
		arg++;
	}
	return (ret_value);
}

static int	check_arg(char *arg, t_env *env)
{
	int	i;
	int	ret;

	i = 0;
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
	{
		print_builtin_error("export", arg);
		ft_putstr_fd("not a valid identifier\n", STDERR_FILENO);
		return (1);
	}
	while (arg[i])
	{
		ret = check_arg2(arg, env, i);
		if (ret == 0)
			return (0);
		else if (ret == 1)
			return (1);
		i++;
	}
	if (already_exists(find_name(arg), NULL, env) == FALSE)
		envadd_elem(env, find_name(arg), NULL, FALSE);
	return (0);
}

int	check_arg2(char *arg, t_env *env, int i)
{
	if (arg[i] == '=')
	{
		if (already_exists(find_name(arg), find_value(arg), env) == FALSE)
			return (envadd_elem(env, find_name(arg), \
					find_value(arg), TRUE));
		return (0);
	}
	if (!ft_isalnum(arg[i]) && arg[i] != '_')
	{
		print_builtin_error("export", arg);
		ft_putstr_fd("not a valid identifier\n", STDERR_FILENO);
		return (1);
	}
	return (2);
}

static int	already_exists(char *name, char *value, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
		{
			if (value)
			{
				env->value = value;
				env->is_env = TRUE;
			}
			return (TRUE);
		}
		env = env->next;
	}
	return (FALSE);
}

static int	print_export(t_env *env)
{
	int		i;
	char	**env_str;

	i = 0;
	env_str = env_to_str(env, TRUE);
	while (env_str[i])
	{
		ft_printf("declare -x %s\n", env_str[i]);
		i++;
	}
	return (0);
}
