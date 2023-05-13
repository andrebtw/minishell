/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthibaul <mthibaul@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 18:08:48 by mthibaul          #+#    #+#             */
/*   Updated: 2023/05/14 01:23:21 by mthibaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "libft.h"

static void	do_dup(int in, int out)
{
	if (dup2(in, 0) < 0 || dup2(out, 1) < 0)
		error("Dup2");
}

void	child(int index, int *pipes_tab)
{
		if (index == 0)
			do_dup(p.infile, p.pipe[1]);
		else if (p.index == p.cmd_nb - 1)
			do_dup(p.pipe[2 * p.index - 2], p.outfile);
		else
			do_dup(p.pipe[2 * p.index - 2], p.pipe[2 * p.index + 1]);
		close_pipes(&p);
}
