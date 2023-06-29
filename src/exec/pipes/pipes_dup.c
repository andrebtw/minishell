/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_dup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthibaul <mthibaul@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 18:08:48 by mthibaul          #+#    #+#             */
/*   Updated: 2023/05/14 15:29:17 by mthibaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipes_dup(t_pipe *pipe, t_cmd *cmd)
{
	if (pipe->index == 0)
	{
		if (cmd->fd_in != STDIN_FILENO && cmd->fd_out == STDOUT_FILENO)
			do_dup(cmd->fd_in, pipe->pipes_tab[1]);
		else if (cmd->fd_in == STDIN_FILENO && cmd->fd_out == STDOUT_FILENO)
        {
            dup2(pipe->pipes_tab[1], 1);
            close(pipe->pipes_tab[1]);
        }
	}
	else if (pipe->index == pipe->cmd_nb - 1)
	{
		if (cmd->fd_out != STDOUT_FILENO && cmd->fd_in == STDIN_FILENO)
			do_dup(pipe->pipes_tab[2 * pipe->index - 2], cmd->fd_out);
		else if (cmd->fd_out == STDOUT_FILENO && cmd->fd_in == STDIN_FILENO)
        {
            dup2(pipe->pipes_tab[2 * pipe->index - 2], 0);
            close(pipe->pipes_tab[2 * pipe->index - 2]);
        }
	}
	else
	{
		if (cmd->fd_in != STDIN_FILENO && cmd->fd_out == STDOUT_FILENO)
			dup2(pipe->pipes_tab[2 * pipe->index + 1], STDOUT_FILENO);
		else if (cmd->fd_out != STDOUT_FILENO && cmd->fd_in == STDIN_FILENO)
			dup2(pipe->pipes_tab[2 * pipe->index - 2], STDIN_FILENO);
		else if (cmd->fd_out == STDOUT_FILENO && cmd->fd_in == STDIN_FILENO)
			do_dup(pipe->pipes_tab[2 * pipe->index - 2], pipe->pipes_tab[2 * pipe->index + 1]);
	}
	close_pipes(pipe);
	return (0);
}
