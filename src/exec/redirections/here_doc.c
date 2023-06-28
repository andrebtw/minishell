/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:09:49 by mthibaul          #+#    #+#             */
/*   Updated: 2023/06/27 12:49:09 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_here_doc(char *av, char *line);
char	*here_doc_env(t_shell *shell, char *line);

int	ft_here_doc(t_shell *shell, char *delimiter)
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
		{

			ft_putstr_fd("warning: here-document at line 2 delimited by end-of-file (wanted `", 2);
			ft_putstr_fd(delimiter, 2);
			ft_putstr_fd("')\n", 2);
			break ;
		}
		else
		{
			line = here_doc_env(shell, line);
			if (check_here_doc(delimiter, line) > 0)
			{
				line = ft_strjoin(line, "\n");
				write(fd, line, ft_strlen(line));
			}
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
