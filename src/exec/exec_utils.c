/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 14:15:00 by mthibaul          #+#    #+#             */
/*   Updated: 2023/05/06 17:22:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *str1, char *str2)
{
	size_t	i;

	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (-1);
		i++;
	}
	if (str1[i] == '\0' && str2[i] == '\0')
		return (0);
	return (1);
}

static int	return_error(int error_code)
{
	errno = error_code;
	return (-1);
}

long long	ft_atoll(const char *nptr)
{
	size_t		index;
	int			sign;
	long long	result;

	index = 0;
	sign = 1;
	result = 0;
	while (ft_isspace(nptr[index]))
		index++;
	if (nptr[index] == '-' || nptr[index] == '+')
	{
		if (nptr[index] == '-')
			sign = -1;
		index++;
	}
	while (ft_isdigit(nptr[index]))
	{
		if ((result * 10 + (nptr[index] - '0') * sign) / 10 != result)
			return (return_error(ERANGE));
		result = result * 10 + (nptr[index] - '0') * sign;
		index++;
	}
	return (result);
}
