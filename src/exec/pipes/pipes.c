/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthibaul <mthibaul@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 17:34:17 by mthibaul          #+#    #+#             */
/*   Updated: 2023/05/14 01:21:38 by mthibaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	close_pipes(int *pipes_tab, int pipe_nb)
{
	int	i;

	i = 0;
	while (i < pipe_nb)
	{
		close(pipes_tab[i]);
		i++;
	}
}

int	do_pipes(int *pipes_tab, int cmd_nb)
{
	int	i;

	i = 0;
	while (i < cmd_nb)
	{
		if (pipe(pipes_tab + 2 * i) < 0)
			return (-1);
		i++;
	}
}

int	pipes(t_env *env, t_cmd *cmd, int cmd_nb)
{
	int	*pipes_tab;
	int	index;

	get_infile(av, &pipex);
	get_outfile(av[ac - 1], &pipex);
	pipes_tab = malloc(sizeof(int) * cmd_nb * 2);
	if (!pipes_tab)
		return (-1);
	if (do_pipes(pipes_tab, cmd_nb) < 0)
		return (-1);
	index = -1;
	while (++index < cmd_nb)
		child(env, cmd);
	close_pipes(pipes_tab, cmd_nb * 2);
	free(pipex.pipe);
	ft_freesplit(pipex.cmd_path);
	unlink(".here_doc"); 
	return (0);
}
