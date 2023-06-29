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
			check_redirections(shell);
			pipes_dup(&pipe, cmd);
            if (find_builtin(shell, cmd, env) < 0)
                exec_cmd(cmd, env, shell);
			if (cmd->here_doc == TRUE)
				unlink(".here_doc");
			reset_fd(shell);
            clean_exit(shell);
        }
		close(pipe.pipes_tab[pipe.index + 1]);
		waitpid(pid, NULL, 0);
		cmd = cmd->next;
		shell->command = shell->command->next;
	}
	close_pipes(&pipe);
	free(pipe.pipes_tab);
	return (0);
}
