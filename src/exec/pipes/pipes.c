/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthibaul <mthibaul@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 17:34:17 by mthibaul          #+#    #+#             */
/*   Updated: 2023/07/10 09:36:05 by mthibaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes(t_pipe *pipe)
{
	int	i;

	i = 0;
	while (i < pipe->cmd_nb * 2)
	{
		close(pipe->pipes_tab[i]);
		i++;
	}
}

int	do_pipes(t_pipe *p)
{
	int	i;

	i = 0;
	while (i < p->cmd_nb)
	{
		if (pipe(p->pipes_tab + 2 * i) < 0)
			return (-1);
		i++;
	}
	return (0);
}

int	pipes(t_env *env, t_cmd *cmd, int cmd_nb, t_shell *shell)
{
	t_pipe	pipe;
	pid_t	pid;
	int		ret_value;

	ret_value = 0;
	pipe.cmd_nb = cmd_nb;
	pipe.pipe_nb = cmd_nb * 2;
	pipe.pipes_tab = malloc(sizeof(int) * pipe.pipe_nb);
	if (!pipe.pipes_tab)
		return (-1);
	if (do_pipes(&pipe) < 0)
		return (-1);
	pipe.index = -1;
	while (++(pipe.index) < cmd_nb && cmd)
	{
		pid = fork();
		if (pid == -1)
			return (-1);
		else if (pid == 0)
		{
			if (check_redirections(shell) != 0)
			{
				close_pipes(&pipe);
				clean_exit(shell);
			}
			pipes_dup(&pipe, cmd);
			close_pipes(&pipe);
			if (find_builtin(shell, cmd, env) < 0)
				exec_cmd(cmd, env, shell);
			clean_exit(shell);
		}
		reset_fd(shell);
		if (is_here_doc(cmd) || cmd->in_out_code[0])
		{
			waitpid(pid, &ret_value, 0);
			if (is_here_doc(cmd))
				unlink(".here_doc");
		}
		cmd = cmd->next;
		shell->command = shell->command->next;
	}
	reset_fd(shell);
	close_pipes(&pipe);
	waitpid(pid, &ret_value, 0);
	shell->last_err_code = ret_value;
	free(pipe.pipes_tab);
	return (0);
}
