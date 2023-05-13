/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthibaul <mthibaul@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 00:02:18 by mthibaul          #+#    #+#             */
/*   Updated: 2023/05/14 00:02:18 by mthibaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_limiter(char *av, char *line)
{
	if (line)
	{
		if (ft_strlen(av) == ft_strlen(line) - 1)
		{
			if (ft_strncmp(av, line, ft_strlen(av)) == 0 && line[0] != 10)
				return (0);
		}
	}
	return (1);
}

/*int	check_here_doc(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->in_out_code[i])
	{
		
	}
}*/

int	here_doc(char *av, t_pipex *pipex)
{
	int		fd;
	char	*line;

	fd = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		error("Here_doc");
	line = NULL;
	while (check_limiter(av, line) > 0)
	{
		free(line);
		write(1, "pipex heredoc> ", 16);
		line = get_next_line(0);
		if (!line)
			error("Get_next_line");
		if (check_limiter(av, line) > 0)
			write(fd, line, ft_strlen(line));
	}
	free(line);
	close(fd);
	pipex->infile = open(".here_doc", O_RDONLY);
	if (pipex->infile < 0)
		error(".here_doc");
}