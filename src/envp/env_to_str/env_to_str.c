/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:13:00 by mthibaul          #+#    #+#             */
/*   Updated: 2023/05/06 17:52:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

int		env_size(t_env *env);
char	*add_env(t_env *env);
void	free_env_str(char **env);

char **env_to_str(t_env *env)
{
	char	**env_str;
	int		i;

	env_str = malloc(sizeof(char *) * (env_size(env) + 1));
	if (!env_str)
		return (NULL);
	i = 0;
	while (env)
	{
		env_str[i] = add_env(env);
		if (!env_str[i])
			return (free_env_str(env_str), NULL);
		env = env->next;
		i++;
	}
	env_str[i++] = NULL;
	return (env_str);
}

int	env_size(t_env *env)
{
	int i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

char	*add_env(t_env *env)
{
	char *env_str;

	env_str = ft_strjoin(env->name, "=");
	if (env->value)
		env_str = ft_strjoin(env_str, env->value);
	return (env_str);
}

void	free_env_str(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}