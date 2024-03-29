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

char	**find_path(t_env *env, t_shell *shell);
char	*find_cmd(t_cmd *cmd, t_env *env, t_shell *shell);
int		find_slash(t_cmd *cmd, t_env *env, char **cmd_path, t_shell *shell);
pid_t	exec_fork(char *cmd_path, char **env_str, t_shell *shell);
void	check_if_print_signal(t_shell *shell);

int	exec_cmd(t_cmd *cmd, t_env *env, t_shell *shell)
{
	int		ret_value;
	char	*cmd_path;
	char	**env_str;
	int		fd;

	cmd_path = NULL;
	if (find_slash(cmd, env, &cmd_path, shell) == 0)
	{
		fd = open(cmd->content[0], O_DIRECTORY);
		if (fd >= 0)
			return (errno = EISDIR, g_code = 126, perror(\
			cmd->content[0]), close(fd), 126);
		cmd_path = NULL;
	}
	else if (cmd_path == NULL)
		return (-1);
	env_str = env_to_str(env, FALSE);
	if (!env_str)
		return (free(cmd_path), malloc_err_exit(shell), 0);
	ret_value = exec_fork(cmd_path, env_str, shell);
	ret_value = sig_check_cmd_signal(ret_value, shell);
	if ((g_code == 130 || g_code == 131))
		ret_value = g_code;
	return (g_code = ret_value, free(\
	cmd_path), free_env_str(env_str), ret_value);
}

int	find_slash(t_cmd *cmd, t_env *env, char **cmd_path, t_shell *shell)
{
	int		i;
	char	*command;

	i = 0;
	command = cmd->content[0];
	while (command[i])
	{
		if (command[i] == '/')
			return (0);
		i++;
	}
	*cmd_path = find_cmd(cmd, env, shell);
	if (!(*cmd_path))
		return (-1);
	return (1);
}

char	*find_cmd(t_cmd *cmd, t_env *env, t_shell *shell)
{
	char	**path;
	char	*cmd_path;
	int		i;

	i = 0;
	path = find_path(env, shell);
	if (!env->name)
		return (NULL);
	while (path[i])
	{
		cmd_path = ft_strjoin(path[i], cmd->content[0]);
		if (!cmd_path)
			return (ft_free_tab(path), malloc_err_exit(shell), NULL);
		if (access(cmd_path, F_OK | R_OK | X_OK) == 0)
			return (ft_free_tab(path), cmd_path);
		free(cmd_path);
		i++;
	}
	ft_putstr_fd(cmd->content[0], STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
	g_code = COMMAND_NOT_FOUND;
	return (ft_free_tab(path), reset_fd(shell), NULL);
}

char	**find_path(t_env *env, t_shell *shell)
{
	char	**path;
	int		i;

	i = 0;
	if (!env->name)
		return (NULL);
	while (ft_strcmp(env->name, "PATH") != 0 && env->next)
		env = env->next;
	path = ft_split(env->value, ':');
	if (!path)
		return (malloc_err_exit(shell), NULL);
	while (path[i])
	{
		path[i] = ft_strjoin_free(path[i], "/", 1, 0);
		if (!path[i])
		{
			while (path[++i])
				free(path[i]);
			return (ft_free_tab(path), malloc_err_exit(shell), NULL);
		}
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
			execve(shell->command->content[0],
				shell->command->content, env_str);
		perror(shell->command->content[0]);
		free_env_str(env_str);
		if (errno == EACCES)
			exit_clean(126, shell);
		exit_clean(127, shell);
	}
	waitpid(pid, &ret_value, 0);
	return (ret_value);
}
