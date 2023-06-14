/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthibaul <mthibaul@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:12:00 by mthibaul          #+#    #+#             */
/*   Updated: 2023/06/08 13:12:00 by mthibaul         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	error_cmd(char *cmd, char *file)
{
	char *error;

	if (cmd != NULL && ft_strcmp(cmd, "") != 0)
	{
		error = ft_strjoin(cmd, ": ");
		error = ft_strjoin(error, file);
	}
	else
		error = file;
	perror(error);
	return (-1);
}