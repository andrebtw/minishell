/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthibaul <mthibaul@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:56:00 by mthibaul          #+#    #+#             */
/*   Updated: 2023/04/04 13:56:00 by mthibaul         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int is_newline(char *arg);
int print_args(char **arg);

int	echo(char **arg)
{
	arg++;
	if (*arg && is_newline(arg[1]))
	{
		arg++;
		if (print_args(arg) != 0)
			return (1);
		if (printf("\n") < 0)
			return (1);
	}
	else if (*arg)
		return (print_args(arg));
	else
		return (1);
}

int is_newline(char *arg)
{
	if (*arg == '-')
	{
		arg++;
		if (*arg == 'n')
		{
			arg++;
			if (*arg == '\0')
				return (1);
		}
	}
	return (0);
}

int print_args(char **arg)
{
	while(*arg)
	{
		if (printf("%s", *arg) < 0)
			return (1);
		arg++;
		if (*arg)
			printf(" ");
	}
	return (0);
}
