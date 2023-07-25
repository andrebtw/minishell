/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:56:00 by mthibaul          #+#    #+#             */
/*   Updated: 2023/07/24 17:08:05 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_newline(char *arg);
int	print_args(char **arg);

int	echo(char **arg)
{
	arg++;
	if (*arg && is_newline(*arg))
	{
		arg++;
		while (*arg && is_newline(*arg))
			arg++;
		if (print_args(arg) != 0)
			return (1);
		return (0);
	}
	else if (*arg)
	{
		if (print_args(arg) != 0)
			return (1);
		if (ft_printf("\n") < 0)
			return (1);
		return (0);
	}
	ft_printf("\n");
	return (0);
}

int	is_newline(char *arg)
{
	if (*arg == '-')
	{
		arg++;
		while (*arg == 'n' || ft_isspace(*arg) == 1)
		{
			arg++;
			if (*arg == '\0')
				return (1);
			if (*arg == '-' && *arg + 1 == 'n')
				arg++;
		}
	}
	return (0);
}

int	print_args(char **arg)
{
	while (*arg)
	{
		if (ft_printf("%s", *arg) < 0)
			return (1);
		arg++;
		if (*arg)
			ft_printf(" ");
	}
	return (0);
}
