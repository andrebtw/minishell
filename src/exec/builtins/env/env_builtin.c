/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 13:17:00 by mthibaul          #+#    #+#             */
/*   Updated: 2023/05/06 17:32:02 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int env_builtin(char **args, t_env *env)
{
	char	**env_str;

	if (args[1])
		return(ft_putstr_fd("🛸~> env: too many arguments\n", STDERR_FILENO), 1);
	env_str = env_to_str(env);
	if (!env_str)
		return (1);
	while (*env_str)
	{
		ft_putstr_fd(*env_str, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		env_str++;
	}
	return (0);
}