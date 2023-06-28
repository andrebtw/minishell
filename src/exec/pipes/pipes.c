/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 17:34:17 by mthibaul          #+#    #+#             */
/*   Updated: 2023/06/27 12:30:00 by anrodri2         ###   ########.fr       */
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
	int		i;

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
            pipes_dup(shell, &pipe, cmd);
            if (find_builtin(shell, cmd, env) < 0)
                exec_cmd(cmd, env);
			if (cmd->here_doc == TRUE)
				unlink(".here_doc");
            exit(0);
        }
		cmd = cmd->next;
	}
	close_pipes(&pipe);
	i = -1;
	while (++i < cmd_nb)
		waitpid(-1, NULL, 0);
	free(pipe.pipes_tab);
	return (0);
}
