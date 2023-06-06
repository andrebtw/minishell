/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthibaul <mthibaul@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 17:34:17 by mthibaul          #+#    #+#             */
/*   Updated: 2023/05/15 23:17:19 by mthibaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	close_pipes(t_pipe *pipe)
{
	int	i;

	i = 0;
	while (i < pipe->pipe_nb)
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
    pid_t   pid;

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
			close(shell->fd_stdout);
			close(shell->fd_stdin);
            pipes_dup(&pipe, cmd);
            if (find_builtin(cmd, env) < 0)
                exec_cmd(cmd, env);
            exit(0);
        }
		cmd = cmd->next;
	}
	int i = 0;
	while (++i < cmd_nb)
		waitpid(-1, NULL, 0);
	close_pipes(&pipe);
	free(pipe.pipes_tab);
	return (0);
}
