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

extern int	g_code;

char	**find_path(t_env *env);
char	*find_cmd(t_cmd *cmd, t_env *env);
int		find_slash(char *cmd);
pid_t	exec_fork(char *cmd_path, char **env_str, t_shell *shell);

int	exec_cmd(t_cmd *cmd, t_env *env, t_shell *shell)
{
	int		ret_value;
	char	*cmd_path;
	char	**env_str;
	int		fd;

	ret_value = 0;
	if (find_slash(cmd->content[0]) == 1)
	{
		cmd_path = find_cmd(cmd, env);
		if (!cmd_path)
			return (-1);
	}
	else
	{
		fd = open(cmd->content[0], O_DIRECTORY);
		if (fd >= 0)
		{
			errno = EISDIR;
			g_code = 126;
			perror(cmd->content[0]);
			return(close(fd), 126);
		}
		cmd_path = NULL;
	}
	env_str = env_to_str(env, FALSE);
	ret_value = exec_fork(cmd_path, env_str, shell);
	sig_check_cmd_signal(ret_value);
	free(cmd_path);
	free_env_str(env_str);
	if (ret_value > 128)
		ret_value = 1;
	g_code = ret_value;
	return (ret_value);
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
	g_code = COMMAND_NOT_FOUND;
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

pid_t	exec_fork(char *cmd_path, char **env_str, t_shell *shell)
{
	pid_t	pid;
	int		ret_value;

	errno = 0;
	pid = fork();
	if (pid < 0)
		return (-1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (cmd_path)
			execve(cmd_path, shell->command->content, env_str);
		else
			execve(shell->command->content[0], shell->command->content, env_str);
		perror(shell->command->content[0]);
		exit_clean(127, shell, shell->env);
	}
	waitpid(pid, &ret_value, 0);
	return (WEXITSTATUS(ret_value));
}
