/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthibaul <mthibaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:04:00 by mthibaul          #+#    #+#             */
/*   Updated: 2023/04/17 13:45:18 by mthibaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_arg(char *arg, t_env *env);
static int	print_export(t_env *env);

int export(t_env *env, char **arg)
{
	if (!arg[1])
		return (print_export(env));
	arg++;
	while (*arg)
	{
		check_arg(*arg, env);
		arg++;
	}
	return (0);
}

static int check_arg(char *arg, t_env *env)
{
	int	i;

	i = 0;
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
	{
		print_builtin_error("export", arg);
		ft_putstr_fd("not a valid identifier\n", STDERR_FILENO);
		return (1);
	}
	while(arg[i])
	{
		if (arg[i] == '=')
			return (envadd_elem(env, find_name(arg), find_value(arg), TRUE));
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			print_builtin_error("export", arg);
			ft_putstr_fd("not a valid identifier\n", STDERR_FILENO);
			return (1);
		}
		i++;
	}
	return (envadd_elem(env, arg, NULL, FALSE));
}

static int	print_export(t_env *env)
{
	int		i;
	char	**env_str;

	i = 0;
	env_str = env_to_str(env, TRUE);
	while (env_str[i])
	{
		printf("declare -x %s\n", env_str[i]);
		i++;
	}
	return (0);
}