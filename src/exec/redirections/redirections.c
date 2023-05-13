/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthibaul <mthibaul@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 00:00:07 by mthibaul          #+#    #+#             */
/*   Updated: 2023/05/14 00:00:07 by mthibaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_infile(char **av, t_pipex *pipex)
{
	if (!pipex->here_doc)
	{
		pipex->infile = open(av[1], O_RDONLY);
		if (pipex->infile < 0)
			error(av[1]);
	}
	else
		here_doc(av[2], pipex);
}

void	get_outfile(char *file, t_pipex *pipex)
{
	if (!pipex->here_doc)
		pipex->outfile = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else
		pipex->outfile = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (pipex->outfile < 0)
		error(file);
}