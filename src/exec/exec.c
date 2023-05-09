/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 16:17:00 by mthibaul          #+#    #+#             */
/*   Updated: 2023/05/09 20:54:10 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtins(t_cmd *cmd, t_env *env)
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
		return (unset(cmd->content, &env));
	else if (ft_strcmp(cmd->content[0], "env") == 0)
		return (env_builtin(cmd->content, env));
	else if (ft_strcmp(cmd->content[0], "exit") == 0)
		return (exit_builtin(cmd->content, env));
	else
		return (-1);
}
