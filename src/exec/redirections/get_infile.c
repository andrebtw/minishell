/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infile.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthibaul <mthibaul@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 12:03:42 by mthibaul          #+#    #+#             */
/*   Updated: 2023/07/13 12:21:57 by mthibaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_code;
static int	check_here_doc(t_cmd *cmd, t_shell *shell);
static int	check_in_redirections(t_cmd *cmd);

int	get_infile(t_shell *shell, t_cmd *cmd)
{
	int	fd_in;
	int	tmp_fd;

	cmd->here_doc = FALSE;
	fd_in = STDIN_FILENO;
	if (!cmd->in_out_code)
		return (fd_in);
	fd_in = check_here_doc(cmd, shell);
	tmp_fd = check_in_redirections(cmd);
	if (fd_in == STDIN_FILENO)
		fd_in = tmp_fd;
	return (fd_in);
}

static int	check_here_doc(t_cmd *cmd, t_shell *shell)
{
	int	i;
	int	last_here_doc;
	int	tmp_fd;

	i = -1;
	tmp_fd = STDIN_FILENO;
	last_here_doc = -1;
	while (cmd->in_out_code[++i])
	{
		if (cmd->in_out_code[i] == IS_HEREDOC)
		{
			last_here_doc = i;
			tmp_fd = ft_here_doc(shell, cmd->in_out[i]);
			cmd->here_doc = TRUE;
			if (tmp_fd == -1)
				return (-1);
		}
		else if (cmd->in_out_code[i] == IS_IN && i > last_here_doc)
			last_here_doc = -1;
	}
	if (last_here_doc == -1)
		tmp_fd = 0;
	return (tmp_fd);
}

static int	check_in_redirections(t_cmd *cmd)
{
	int	i;
	int	tmp_fd;

	i = -1;
	tmp_fd = STDIN_FILENO;
	while (cmd->in_out_code[++i])
	{
		if (cmd->in_out_code[i] == IS_IN || cmd->in_out_code[i] == IS_HEREDOC)
		{
			if (tmp_fd != STDIN_FILENO)
				close(tmp_fd);
			if (cmd->in_out_code[i] == IS_IN)
			{
				tmp_fd = open(cmd->in_out[i], O_RDONLY);
				if (tmp_fd < 0)
				{
					g_code = 1;
					return (error_cmd(cmd->content[0], cmd->in_out[i]));
				}
			}
		}
	}
	return (tmp_fd);
}
