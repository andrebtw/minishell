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
	int fd;

	if (pipe->index == 0)
	{
		fd = get_infile(cmd);
		printf("pipe in = %d\n", fd);
		if (fd < 0)
			return (-1);
		if (fd != STDIN_FILENO)
			do_dup(fd, pipe->pipes_tab[1]);
		else
			dup2(pipe->pipes_tab[1], 1);
	}
	else if (pipe->index == pipe->cmd_nb - 1)
	{
		fd = get_outfile(cmd);
		if (fd < 0)
			return (-1);
		if (fd != STDOUT_FILENO)
			do_dup(pipe->pipes_tab[2 * pipe->index - 2], fd);
		else
			dup2(pipe->pipes_tab[2 * pipe->index -2], 0);
	}
	else
		do_dup(pipe->pipes_tab[2 * pipe->index - 2], pipe->pipes_tab[2 * pipe->index + 1]);
	close_pipes(pipe);
	return (0);
}
