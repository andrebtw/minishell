/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 13:12:00 by mthibaul          #+#    #+#             */
/*   Updated: 2023/06/29 14:50:15 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	error_cmd(char *cmd, char *file, t_shell *shell)
{
	char	*error;

	if (cmd != NULL && ft_strcmp(cmd, "") != 0)
	{
		error = ft_strjoin_free(cmd, ": ", 0, 0);
		if (!error)
			malloc_err_exit(shell);
		error = ft_strjoin_free(error, file, 1, 0);
	}
	else
		error = file;
	perror(error);
	free(error);
	return (-1);
}
