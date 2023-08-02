/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:17:00 by mthibaul          #+#    #+#             */
/*   Updated: 2023/07/11 04:07:44 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_code;
int			check_cmd(t_shell *shell, t_env *env, t_cmd *cmd);
static int	check_pipe(t_shell *shell, int cmd_nb);

int	cmd_nb(t_shell *shell)
{
	int		count;
	t_cmd	*tmp;

	g_code = 0;
	shell->fd_stdin = dup(STDIN_FILENO);
	shell->fd_stdout = dup(STDOUT_FILENO);
	count = 0;
	tmp = shell->command;
	while (tmp)
	{
		tmp = tmp->next;
		count++;
	}
	return (check_pipe(shell, count));
}

static int	check_pipe(t_shell *shell, int cmd_nb)
{
	if (cmd_nb > 1)
	{
		pipes(shell->command, cmd_nb, shell);
		unlink("/tmp/.here_doc");
		return (0);
	}
	else
	{
		if (check_redirections(shell) < 0)
			return (-1);
		if (check_cmd(shell, shell->env, shell->command) != 0)
			return (-1);
		reset_fd(shell);
		unlink("/tmp/.here_doc");
		return (0);
	}
}

int	check_cmd(t_shell *shell, t_env *env, t_cmd *cmd)
{
	int	ret_value;

	if (!cmd->content[0])
		return (0);
	if (cmd->content[0][0] == '\0')
		return (ft_putstr_fd("'': command not found\n", STDERR_FILENO), 0);
	ret_value = find_builtin(shell, cmd, env);
	if (ret_value != -1)
	{
		g_code = ret_value;
		return (ret_value);
	}
	else if (exec_cmd(cmd, env, shell) != -1)
		return (0);
	return (-1);
}

int	find_builtin(t_shell *shell, t_cmd *cmd, t_env *env)
{
	if (ft_strcmp(cmd->content[0], "echo") == 0)
		return (echo(cmd->content));
	else if (ft_strcmp(cmd->content[0], "cd") == 0)
		return (cd(env, cmd->content, shell));
	else if (ft_strcmp(cmd->content[0], "pwd") == 0)
		return (pwd(shell));
	else if (ft_strcmp(cmd->content[0], "export") == 0)
		return (export(env, cmd->content, shell));
	else if (ft_strcmp(cmd->content[0], "unset") == 0)
		return (unset(cmd->content, env, shell));
	else if (ft_strcmp(cmd->content[0], "env") == 0)
		return (env_builtin(cmd->content, env, shell));
	else if (ft_strcmp(cmd->content[0], "exit") == 0)
		return (exit_builtin(shell, cmd->content));
	else
		return (-1);
}
