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

static int	do_dup(int in, int out)
{
	if (dup2(in, 0) < 0 || dup2(out, 1) < 0)
		return (-1);
	return (0);
}

int	pipes_dup(t_pipe *pipe)
{
		if (pipe->index == 0)
			do_dup(0, pipe->pipes_tab[1]);
		else if (pipe->index == pipe->cmd_nb - 1)
			do_dup(pipe->pipes_tab[2 * pipe->index - 2], 1);
		else
			do_dup(pipe->pipes_tab[2 * pipe->index - 2], pipe->pipes_tab[2 * pipe->index + 1]);
		close_pipes(pipe);
		return (0);
}
