/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthibaul <mthibaul@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:04:00 by mthibaul          #+#    #+#             */
/*   Updated: 2023/04/12 16:04:00 by mthibaul         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static int	check_arg(char *arg, t_env *env);
static int	add_to_env(char *arg, t_env *env);

int export(t_env *env, char **arg)
{
	while (*arg)
	{
		check_arg(*arg, env);
		arg++;
	}
}

static int check_arg(char *arg, t_env *env)
{
	int	i;

	i = 0;
	if ((arg[i] < 'A' || arg[i] > 'Z') && (arg[i] < 'a' || arg[i] > 'z'))
	{
		print_builtin_error("export", arg);
		ft_putstr_fd("not a valid identifier\n", STDERR_FILENO);
		return (1);
	}
	while(arg[i])
	{
		if (arg[i] == '=')
			return (envadd_elem(&env, find_name(arg), find_value(arg)));
		i++;
	}
}