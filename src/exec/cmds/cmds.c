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
char	*find_cmd(t_cmd *cmd, t_env *env);
int		find_slash(char *cmd);

int	exec_cmd(t_cmd *cmd, t_env *env)
{
	char	*cmd_path;
	char	**env_str;
    pid_t   pid;

    cmd_path = find_cmd(cmd, env);
    if (!cmd_path)
        return (-1);
    env_str = env_to_str(env);
    pid = fork();
    if (pid < 0)
        return (-1);
    else if (pid == 0)
	{
		if (find_slash(cmd->content[0]) == 1)
			execve(cmd_path, cmd->content, env_str);
		else
			execve(cmd->content[0], cmd->content, env_str);
	}
	waitpid(pid, NULL, 0);
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

char	*find_cmd(t_cmd *cmd, t_env *env)
{
	char	**path;
	char	*cmd_path;

	path = find_path(env);
	while (*path)
	{
		cmd_path = ft_strjoin(*path, cmd->content[0]);
		if (!cmd_path)
			return (NULL);
		if (access(cmd_path, F_OK | R_OK | X_OK) == 0)
			return (cmd_path);
		path++;
	}
	ft_putstr_fd(cmd->content[0], STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	return (0);
}

char	**find_path(t_env *env)
{
	char	**path;
	int		i;

	i = 0;
	while (ft_strcmp(env->name, "PATH") != 0)
		env = env->next;
	path = ft_split(env->value, ':');
	if (!path)
		return (NULL);
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		if (!path[i])
			return (NULL);
		i++;
	}
	return (path);
}