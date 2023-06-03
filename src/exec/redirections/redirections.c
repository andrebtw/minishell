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

int	check_redirections(t_cmd *cmd)
{
    cmd->fd_stdin = STDIN_FILENO;
    cmd->fd_stdout = STDOUT_FILENO;
	cmd->fd_in = get_infile(cmd);
	cmd->fd_out = get_outfile(cmd);
	if (cmd->fd_in != cmd->fd_stdin && cmd->fd_out != cmd->fd_stdout)
		return (do_dup(cmd->fd_in, cmd->fd_out));
	else if (cmd->fd_in != cmd->fd_stdin)
		return (dup2(cmd->fd_in, STDIN_FILENO), close(cmd->fd_in));
	else if (cmd->fd_out != cmd->fd_stdout)
		return (dup2(cmd->fd_out, STDOUT_FILENO), close(cmd->fd_out));
	return (0);
}

int	get_infile(t_cmd *cmd)
{
	int infile;
	int fd_in;
	int i;

	infile = -1;
	i = -1;
	fd_in = STDIN_FILENO;
	if (!cmd->in_out_code)
		return (fd_in);
	while (cmd->in_out_code[++i])
	{
		if (cmd->in_out_code[i] == IS_IN)
			infile = i;
	}
	if (infile >= 0)
		fd_in = open(cmd->in_out[infile], O_RDONLY);
	return (fd_in);
}

int	get_outfile(t_cmd *cmd)
{
	int outfile;
	int	fd_out;
	int tmp;
	int append;
	int i;

	outfile = -1;
	i = -1;
	fd_out = STDOUT_FILENO;
	if (!cmd->in_out_code)
		return (fd_out);
	while (cmd->in_out_code[++i])
	{
		if (cmd->in_out_code[i] == IS_OUT)
		{
			outfile = i;
			append = 0;
			tmp = open(cmd->in_out[i], O_CREAT | O_TRUNC, 0644);
			close(tmp);
		}
		else if (cmd->in_out_code[i] == IS_OUT_APPEND)
		{
			outfile = i;
			append = 1;
			tmp = open(cmd->in_out[i], O_CREAT | O_APPEND, 0644);
			close(tmp);
		}
	}
	if (outfile >= 0)
	{
		if (append == 1)
			fd_out = open(cmd->in_out[outfile], O_WRONLY | O_APPEND, 0644);
		else
			fd_out = open(cmd->in_out[outfile], O_WRONLY, 0644);
	}
	return(fd_out);
}

int	do_dup(int in, int out)
{
	if (dup2(in, STDIN_FILENO) < 0 || dup2(out, STDOUT_FILENO) < 0)
		return (-1);
    close(in);
    close(out);
	return (0);
}

int reset_fd(t_cmd *cmd)
{
    if (STDIN_FILENO != cmd->fd_stdin)
    {
        dup2(cmd->fd_stdin, STDIN_FILENO);
        close(cmd->fd_stdin);
    }
    if (STDOUT_FILENO != cmd->fd_stdout)
    {
        dup2(cmd->fd_stdout, STDOUT_FILENO);
        close(cmd->fd_stdout);
    }
    return (0);
}