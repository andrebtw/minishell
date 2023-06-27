/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_dup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 18:08:48 by mthibaul          #+#    #+#             */
/*   Updated: 2023/06/27 12:29:36 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipes_dup(t_shell *shell, t_pipe *pipe, t_cmd *cmd)
{
	int fd;

	if (pipe->index == 0)
	{
		fd = get_infile(shell, cmd);
		if (fd < 0)
			return (-1);
		if (fd != STDIN_FILENO)
			do_dup(fd, pipe->pipes_tab[1]);
		else
        {
            dup2(pipe->pipes_tab[1], 1);
            close(pipe->pipes_tab[1]);
        }
	}
	else if (pipe->index == pipe->cmd_nb - 1)
	{
		fd = get_outfile(cmd);
		if (fd < 0)
			return (-1);
		if (fd != STDOUT_FILENO)
			do_dup(pipe->pipes_tab[2 * pipe->index - 2], fd);
		else
        {
            dup2(pipe->pipes_tab[2 * pipe->index - 2], 0);
            close(pipe->pipes_tab[2 * pipe->index - 2]);
        }
	}
	else
		do_dup(pipe->pipes_tab[2 * pipe->index - 2], pipe->pipes_tab[2 * pipe->index + 1]);
	close_pipes(pipe);
	return (0);
}
