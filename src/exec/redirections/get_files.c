/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthibaul <mthibaul@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 16:53:00 by mthibaul          #+#    #+#             */
/*   Updated: 2023/07/20 16:53:00 by mthibaul         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

extern int	g_code;
static int	open_file(int outfile, int append, int tmp_fd_in, t_cmd *cmd);

int	get_files(t_shell *shell, t_cmd *cmd)
{
	int	tmp_fd_in;
	int	outfile;
	int	append;
	int	i;

	i = -1;
	outfile = -1;
	append = -1;
	tmp_fd_in = STDIN_FILENO;
	cmd->here_doc = FALSE;
	if (!cmd->in_out_code)
		return (0);
	cmd->fd_in = find_here_doc(cmd, shell);
	while (cmd->in_out_code[++i])
	{
		if (cmd->in_out_code[i] == IS_IN || cmd->in_out_code[i] == IS_HEREDOC)
			tmp_fd_in = check_in_redirections(cmd, i);
		else
			check_out_redirections(i, &outfile, &append, cmd);
		if (outfile == -2 || tmp_fd_in < 0)
			return (g_code = 1, -1);
	}
	return (open_file(outfile, append, tmp_fd_in, cmd));
}

static int	open_file(int outfile, int append, int tmp_fd_in, t_cmd *cmd)
{
	if (outfile >= 0)
	{
		if (append == 1)
			cmd->fd_out = open(cmd->in_out[outfile], O_WRONLY | O_APPEND, 0644);
		else
			cmd->fd_out = open(cmd->in_out[outfile], O_WRONLY, 0644);
	}
	if (cmd->fd_in == STDIN_FILENO)
		cmd->fd_in = tmp_fd_in;
	return (0);
}
