/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthibaul <mthibaul@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 18:08:46 by mthibaul          #+#    #+#             */
/*   Updated: 2023/01/12 14:45:23 by mthibaul         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "libft.h"

void	free_pipex(t_pipex *p)
{
	free(p->pipe);
	free(p->cmd);
	ft_freesplit(p->cmd_args);
	ft_freesplit(p->cmd_path);
}

int	err_msg(char *err)
{
	write(2, err, ft_strlen(err));
	return (1);
}

void	error(char *err)
{
	perror(err);
	exit(1);
}
