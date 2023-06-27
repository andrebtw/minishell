/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:17:00 by mthibaul          #+#    #+#             */
/*   Updated: 2023/06/07 11:12:54 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
extern int	g_state;

int	check_cmd(t_shell *shell, t_env *env, t_cmd *cmd);

int	cmd_nb(t_shell *shell)
{
	int		count;
	t_cmd	*tmp;

	g_state = EXECUTION;
	count = 0;
	tmp = shell->command;
	while (tmp)
	{
		tmp = tmp->next;
		count++;
	}
	if (count > 1)
	{
		pipes(shell->env, shell->command, count, shell);
		return (0);
	}
	else
	{
		if (check_redirections(shell) < 0)
			return (-1);
		if (check_cmd(shell, shell->env, shell->command) < 0)
			return (-1);
		if (shell->command->here_doc == TRUE)
			unlink(".here_doc");
		reset_fd(shell);
		return (0);
	}
}

int	check_cmd(t_shell *shell, t_env *env, t_cmd *cmd)
{
	if (!cmd->content[0])
		return (0);
	if (cmd->content[0][0] == '\0')
		return (ft_putstr_fd("'': command not found\n", STDERR_FILENO), 0);
	if (find_builtin(shell, cmd, env) != -1)
		return (0);
	else if (exec_cmd(cmd, env) != -1)
		return (0);
	return (-1);
}

int find_builtin(t_shell *shell, t_cmd *cmd, t_env *env)
{
        if (ft_strcmp(cmd->content[0], "echo") == 0)
            return (echo(cmd->content));
        else if (ft_strcmp(cmd->content[0], "cd") == 0)
            return (cd(env, cmd->content, shell));
        else if (ft_strcmp(cmd->content[0], "pwd") == 0)
            return (pwd());
        else if (ft_strcmp(cmd->content[0], "export") == 0)
            return (export(env, cmd->content));
        else if (ft_strcmp(cmd->content[0], "unset") == 0)
            return (unset(cmd->content, env));
        else if (ft_strcmp(cmd->content[0], "env") == 0)
            return (env_builtin(cmd->content, env));
        else if (ft_strcmp(cmd->content[0], "exit") == 0)
            return (exit_builtin(shell, cmd->content, env));
        else
            return (-1);
}
