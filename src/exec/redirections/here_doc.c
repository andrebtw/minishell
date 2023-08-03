/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthibaul <mthibaul@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:09:49 by mthibaul          #+#    #+#             */
/*   Updated: 2023/07/13 13:24:18 by mthibaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_code;
static int	check_here_doc(char *av, char *line);
char		*here_doc_env(t_shell *shell, char *line);
static int	get_input(char *delimiter, int fd, t_shell *shell);
static int	check_line(char *delimiter, char *line, int fd, t_shell *shell);

int	ft_here_doc(t_shell *shell, char *delimiter)
{
	int		fd;

	unlink("/tmp/.here_doc");
	fd = open("/tmp/.here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	if (get_input(delimiter, fd, shell) != 0)
		return (-1);
	close(fd);
	fd = open("/tmp/.here_doc", O_RDONLY);
	signal(SIGQUIT, (void *)SIG_IGN);
	signal(SIGINT, (void *)SIG_IGN);
	return (fd);
}

static int	get_input(char *delimiter, int fd, t_shell *shell)
{
	char	*line;

	line = NULL;
	while (check_here_doc(delimiter, line) > 0)
	{
		free(line);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, (void *)sig_handler_heredoc);
		rl_getc_function = getc;
		line = readline("> ");
		if (g_code == 130)
		{
			signal(SIGQUIT, SIG_IGN);
			signal(SIGINT, SIG_IGN);
			close(fd);
			return (-1);
		}
		if (check_line(delimiter, line, fd, shell) != 0)
			break ;
	}
	free(line);
	return (0);
}

static int	check_here_doc(char *delimiter, char *line)
{
	if (line)
	{
		if (ft_strcmp(delimiter, line) == 0 && line[0] != 10)
			return (0);
	}
	return (1);
}

int	check_line(char *delimiter, char *line, int fd, t_shell *shell)
{
	if (!line)
	{
		ft_putstr_fd("warning: here-document at line 1 ", 2);
		ft_putstr_fd("delimited by end-of-file (wanted `", 2);
		ft_putstr_fd(delimiter, 2);
		ft_putstr_fd("')\n", 2);
		g_code = 0;
		return (-1);
	}
	else
	{
		line = here_doc_env(shell, line);
		if (check_here_doc(delimiter, line) > 0)
		{
			line = ft_strjoin_free(line, "\n", 1, 0);
			if (!line)
				malloc_err_exit(shell);
			write(fd, line, ft_strlen(line));
		}
	}
	return (free(line), 0);
}
