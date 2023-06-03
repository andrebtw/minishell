/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthibaul <mthibaul@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:17:00 by mthibaul          #+#    #+#             */
/*   Updated: 2023/05/14 15:09:11 by mthibaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_cmd(t_env *env, t_cmd *cmd);

int	cmd_nb(t_shell *shell)
{
	int		count;
	t_cmd	*tmp;
	int		fd_in;
	int		fd_out;

	fd_in = dup(STDIN_FILENO);
	fd_out = dup(STDOUT_FILENO);
	count = 0;
	tmp = shell->command;
	while (tmp)
	{
		tmp = tmp->next;
		count++;
	}
	if (count > 1)
	{
		pipes(shell->env, shell->command, count);
		return (0);
	}
	else
	{
		if (check_cmd(shell->env, shell->command) < 0)
			return (-1);
		close(shell->command->fd_in);
		close(shell->command->fd_out);
		dup2(fd_in, STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		return (0);
	}
}

int	check_cmd(t_env *env, t_cmd *cmd)
{
	check_redirections(cmd);
	if (!cmd->content[0])
		return (0);
	if (find_builtin(cmd, env) != -1)
		return (0);
	else if (exec_cmd(cmd, env) != -1)
		return (0);
	return (-1);
}

int find_builtin(t_cmd *cmd, t_env *env)
{
        if (ft_strcmp(cmd->content[0], "echo") == 0)
            return (echo(cmd->content));
        else if (ft_strcmp(cmd->content[0], "cd") == 0)
            return (cd(env, cmd->content));
        else if (ft_strcmp(cmd->content[0], "pwd") == 0)
            return (pwd());
        else if (ft_strcmp(cmd->content[0], "export") == 0)
            return (export(env, cmd->content));
        else if (ft_strcmp(cmd->content[0], "unset") == 0)
            return (unset(cmd->content, env));
        else if (ft_strcmp(cmd->content[0], "env") == 0)
            return (env_builtin(cmd->content, env));
        else if (ft_strcmp(cmd->content[0], "exit") == 0)
            return (exit_builtin(cmd->content, env));
        else
            return (-1);
}