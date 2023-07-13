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
	shell->command->fd_in = get_infile(shell, shell->command);
	shell->command->fd_out = get_outfile(shell->command);
	if (shell->command->fd_in < 0 || shell->command->fd_out < 0)
		return (-1);
	if (shell->command->fd_in != STDIN_FILENO
		&& shell->command->fd_out != STDOUT_FILENO)
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

int	do_dup(int in, int out)
{
	if (dup2(in, STDIN_FILENO) < 0 || dup2(out, STDOUT_FILENO) < 0)
		return (-1);
	close(in);
	close(out);
	return (0);
}

int	reset_fd(t_shell *shell)
{
	dup2(shell->fd_stdin, STDIN_FILENO);
	close(shell->fd_stdin);
	dup2(shell->fd_stdout, STDOUT_FILENO);
	close(shell->fd_stdout);
	return (0);
}
