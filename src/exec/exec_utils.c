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

#include "../../incl/minishell.h"

int ft_strcmp(char *str1, char *str2)
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

static int	ft_check_if_of(long long number, int neg_mult, size_t nb_length)
{
	if (!number)
		return (0);
	if (nb_length >= 20)
	{
		if (neg_mult == 1)
			return (-1);
		else
			return (0);
	}
	if (neg_mult == 1)
	{
		if ((unsigned long long)number >= __LONG_LONG_MAX__)
			return (-1);
	}
	else
	{
		if ((unsigned long long)number - 1 >= __LONG_LONG_MAX__)
			return (0);
	}
	return (number * neg_mult);
}

long long int	atoll(const char *nptr)
{
	long long		number;
	int				neg_mult;
	int				i;
	size_t			nb_length;

	i = 0;
	number = 0;
	neg_mult = 1;
	nb_length = 0;
	while (ft_isspace(nptr[i]) == 1)
		i++;
	if (nptr[i] == '+')
		i++;
	else if (nptr[i] == '-')
	{
		i++;
		neg_mult = -1;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		number = number * 10 + nptr[i++] - '0';
		if (nptr[i - 1] != '0' || (nptr[i - 1] == '0' && number))
			nb_length++;
	}
	return (ft_check_if_of(number, neg_mult, nb_length));
}