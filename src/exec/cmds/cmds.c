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

#include "../../../incl/minishell.h"

char	**find_path(t_env *env);

int	find_cmd(t_cmd *cmd, t_env *env)
{
	char	**path;
	char	**env_str;
	char	*cmd_path;

	path = find_path(env);
	while (*path)
	{
		cmd_path = ft_strjoin(*path, cmd->content[0]);
		if (!cmd_path)
			return (-1);
		if (access(cmd_path, F_OK | R_OK | X_OK) == 0)
		{
			env_str = env_to_str(env);
			execve(*path, cmd->content, env_str);
			return (-1);
		}
		path++;
	}
	ft_putstr_fd("🛸~> command not found: ", STDERR_FILENO);
	ft_putstr_fd(cmd->content[0], STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
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