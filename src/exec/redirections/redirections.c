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

int	check_redirections(t_shell *shell)
{
    shell->fd_stdin = dup(STDIN_FILENO);
    shell->fd_stdout = dup(STDOUT_FILENO);
	shell->command->fd_in = get_infile(shell->command);
	shell->command->fd_out = get_outfile(shell->command);
	if (shell->command->fd_in < 0 || shell->command->fd_out < 0)
		return (-1);
	if (shell->command->fd_in != STDIN_FILENO && shell->command->fd_out != STDOUT_FILENO)
		return (do_dup(shell->command->fd_in, shell->command->fd_out));
	else if (shell->command->fd_in != STDIN_FILENO)
	{
		if (dup2(shell->command->fd_in, STDIN_FILENO) < 0)
			return (-1);
		return (close(shell->command->fd_in), 0);
	}
	else if (shell->command->fd_out != STDOUT_FILENO)
	{
		if (dup2(shell->command->fd_out, STDOUT_FILENO) < 0)
			return (-1);
		return (close(shell->command->fd_out), 0);
	}
	return (0);
}

int	get_infile(t_cmd *cmd)
{
	int fd_in;
	int tmp_fd;
	int i;

	i = -1;
	cmd->here_doc = FALSE;
	fd_in = STDIN_FILENO;
	tmp_fd = fd_in;
	if (!cmd->in_out_code)
		return (fd_in);
	while (cmd->in_out_code[++i])
	{
		if (cmd->in_out_code[i] == IS_HEREDOC)
			tmp_fd = ft_here_doc(cmd->in_out[i]);
	}
	if (i > 0 && cmd->in_out_code[--i] == IS_HEREDOC)
		fd_in = tmp_fd;
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
					return (error_cmd(cmd->content[0], cmd->in_out[i]));
			}
		}
	}
	if (fd_in == STDIN_FILENO)
		fd_in = tmp_fd;
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
	tmp = STDOUT_FILENO;
	if (!cmd->in_out_code)
		return (fd_out);
	while (cmd->in_out_code[++i])
	{
		if (tmp != STDOUT_FILENO)
			close(tmp);
		if (cmd->in_out_code[i] == IS_OUT)
		{
			outfile = i;
			append = 0;
			tmp = open(cmd->in_out[i], O_CREAT | O_TRUNC | O_WRONLY, 0644);
		}
		else if (cmd->in_out_code[i] == IS_OUT_APPEND)
		{
			outfile = i;
			append = 1;
			tmp = open(cmd->in_out[i], O_CREAT | O_APPEND, 0644);
		}
		if (tmp < 0)
			return (error_cmd(cmd->content[0], cmd->in_out[outfile]));
	}
	if (outfile >= 0)
	{
		if (append == 1)
			fd_out = open(cmd->in_out[outfile], O_WRONLY | O_APPEND, 0644);
		else
			fd_out = open(cmd->in_out[outfile], O_WRONLY, 0644);
	}
	if (fd_out < 0)
		error_cmd(cmd->content[0], cmd->in_out[outfile]);
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

int reset_fd(t_shell *shell)
{
    dup2(shell->fd_stdin, STDIN_FILENO);
	close(shell->fd_stdin);
    dup2(shell->fd_stdout, STDOUT_FILENO);
	close(shell->fd_stdout);
	return (0);
}