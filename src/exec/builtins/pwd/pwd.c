/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthibaul <mthibaul@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 15:59:00 by mthibaul          #+#    #+#             */
/*   Updated: 2023/04/12 15:59:00 by mthibaul         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	pwd(void)
{
	char	*buf;

	buf = getcwd(buf, 0);
	if (!buf)
		return (1);
	ft_putstr_fd(buf, STDOUT_FILENO);
	return (0);
}
