/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthibaul <mthibaul@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 18:35:06 by mthibaul          #+#    #+#             */
/*   Updated: 2023/05/06 18:35:06 by mthibaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
extern int	g_state;

char	**find_path(t_env *env);
char	*find_cmd(t_cmd *cmd, t_env *env, t_shell *shell);
int		find_slash(char *cmd);

int	exec_cmd(t_cmd *cmd, t_env *env, t_shell *shell)
{
	int 	ret_value;
	char	*cmd_path;
	char	**env_str;
    pid_t   pid;

	ret_value = 0;
	if (find_slash(cmd->content[0]) == 1)
	{
		cmd_path = find_cmd(cmd, env, shell);
		if (!cmd_path)
			return (-1);
	}
	else
		cmd_path = NULL;
    env_str = env_to_str(env, FALSE);
    pid = fork();
    if (pid < 0)
        return (-1);
	else if (cmd_path && pid == 0)
	{
		execve(cmd_path, cmd->content, env_str);
		exit_builtin(NULL, NULL, env);
	}
	else if (pid == 0)
	{
		execve(cmd->content[0], cmd->content, env_str);
		exit_builtin(NULL, NULL, env);
	}
	waitpid(pid, &ret_value, 0);
	free(cmd_path);
	free_env_str(env_str);
	shell->last_err_code = ret_value;
	return (0);
}

int	find_slash(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (0);
		i++;
	}
	return (1);
}

char	*find_cmd(t_cmd *cmd, t_env *env, t_shell *shell)
{
	char	**path;
	char	*cmd_path;
	int		i;

	i = 0;
	path = find_path(env);
	while (path[i])
	{
		cmd_path = ft_strjoin(path[i], cmd->content[0]);
		if (!cmd_path)
			return (ft_free_tab(path), NULL);
		if (access(cmd_path, F_OK | R_OK | X_OK) == 0)
			return (ft_free_tab(path), cmd_path);
		free(cmd_path);
		i++;
	}
	ft_putstr_fd(cmd->content[0], STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	shell->last_err_code = COMMAND_NOT_FOUND;
	return (ft_free_tab(path), NULL);
}

char	**find_path(t_env *env)
{
	char	**path;
	int		i;

	i = 0;
	while (ft_strcmp(env->name, "PATH") != 0 && env->next)
		env = env->next;
	path = ft_split(env->value, ':');
	if (!path)
		return (NULL);
	while (path[i])
	{
		path[i] = ft_strjoin_free(path[i], "/", 1, 0);
		if (!path[i])
			return (NULL);
		i++;
	}
	return (path);
}
