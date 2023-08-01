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

int	env_builtin(char **args, t_env *env, t_shell *shell)
{
	char	**env_str;
	int		i;

	i = 0;
	if (!env->name)
		return (0);
	if (args[1])
		return (ft_putstr_fd("env: too many arguments\n", STDERR_FILENO), 1);
	env_str = env_to_str(env, FALSE);
	if (!env_str)
		malloc_err_exit(shell);
	while (env_str[i])
	{
		ft_putstr_fd(env_str[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		i++;
	}
	return (free_env_str(env_str), 0);
}
