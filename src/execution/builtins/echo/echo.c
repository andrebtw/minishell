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
#include "../../../../incl/minishell.h"

int is_newline(char *arg);

int	echo(char **arg)
{
	arg++;
	if (is_newline(*arg))
	{
		arg++;
		while (*arg)
		{
			printf("%s", *arg);
			arg++;
			if (*arg)
				printf(" ");
		}
		return (printf("\n"), 0);
	}
	else
	{
		while(*arg)
		{
			printf("%s", *arg);
			arg++;
			if (*arg)
				printf(" ");
		}
		return (0);
	}
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
