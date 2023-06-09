/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:39:17 by anrodri2          #+#    #+#             */
/*   Updated: 2023/03/11 17:41:43 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_num(char *str);

int	exit_builtin(t_shell *shell, char **args, t_env *env)
{
	long long int return_value;

	printf("exit\n");
	if (args[1])
	{
		if (args[2])
		{
			return (ft_putstr_fd("exit: too many arguments\n", STDERR_FILENO), 0);
		}
		return_value = atoll(args[1]);
		if (!is_num || )
		{
			ft_putstr_fd("exit: ", STDERR_FILENO);
			ft_putstr_fd(args[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			return (0);
		}
	}
	return (0);
}

int	is_num(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (FALSE);
		str++;
	}
	return (TRUE);
}