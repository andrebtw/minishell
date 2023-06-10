/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthibaul <mthibaul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:09:49 by mthibaul          #+#    #+#             */
/*   Updated: 2023/02/03 15:08:20 by mthibaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_here_doc(char *av, char *line);

int	ft_here_doc(char *delimiter)
{
	int		fd;
	char	*line;

	unlink(".here_doc");
	fd = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	line = NULL;
	while (check_here_doc(delimiter, line) > 0)
	{
		free(line);
		line = readline("> ");
		if (!line)
			return (-1);
		if (check_here_doc(delimiter, line) > 0)
		{
			line = ft_strjoin(line, "\n");
			write(fd, line, ft_strlen(line));
		}
	}
	free(line);
	close(fd);
	fd = open(".here_doc", O_RDONLY);
	return (fd);
}

int	check_here_doc(char *delimiter, char *line)
{
	if (line)
	{
		if (ft_strcmp(delimiter, line) == 0 && line[0] != 10)
			return (0);
	}
	return (1);
}
