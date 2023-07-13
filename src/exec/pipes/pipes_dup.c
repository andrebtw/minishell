/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_dup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthibaul <mthibaul@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 18:08:48 by mthibaul          #+#    #+#             */
/*   Updated: 2023/07/10 09:34:21 by mthibaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipes_dup2(t_pipe *pipe, t_cmd *cmd, int *ret_value);

int	pipes_dup(t_pipe *p, t_cmd *cmd)
{
	int	ret_value;

	ret_value = 0;
	if (p->index == 0)
	{
		if (cmd->fd_out == STDOUT_FILENO)
		{
			ret_value = dup2(p->pipes_tab[1], 1);
			close(p->pipes_tab[1]);
		}
	}
	else if (p->index == p->cmd_nb - 1)
	{
		if (cmd->fd_in == STDIN_FILENO)
		{
			ret_value = dup2(p->pipes_tab[2 * p->index - 2], STDIN_FILENO);
			close(p->pipes_tab[2 * p->index - 2]);
		}
	}
	else
		pipes_dup2(p, cmd, &ret_value);
	return (ret_value);
}

void	pipes_dup2(t_pipe *pipe, t_cmd *cmd, int *ret_value)
{
	if (cmd->fd_in != STDIN_FILENO && cmd->fd_out == STDOUT_FILENO)
	{
		*ret_value = dup2(pipe->pipes_tab[2 * pipe->index + 1], STDOUT_FILENO);
		close(pipe->pipes_tab[2 * pipe->index + 1]);
	}
	else if (cmd->fd_out != STDOUT_FILENO && cmd->fd_in == STDIN_FILENO)
	{
		*ret_value = dup2(pipe->pipes_tab[2 * pipe->index - 2], STDIN_FILENO);
		close(pipe->pipes_tab[2 * pipe->index - 2]);
	}
	else if (cmd->fd_out == STDOUT_FILENO && cmd->fd_in == STDIN_FILENO)
		*ret_value = do_dup(pipe->pipes_tab[2 * pipe->index - 2], \
			pipe->pipes_tab[2 * pipe->index + 1]);
}
