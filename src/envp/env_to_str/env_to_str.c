/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthibaul <mthibaul@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:13:00 by mthibaul          #+#    #+#             */
/*   Updated: 2023/07/13 14:57:21 by mthibaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_size(t_env *env);
static char	*add_env(t_env *env, int quotes);

char	**env_to_str(t_env *env, int quotes)
{
	char	**env_str;
	int		i;

	env_str = malloc(sizeof(char *) * (env_size(env) + 1));
	if (!env_str)
		return (NULL);
	i = 0;
	while (env)
	{
		if ((quotes == FALSE && env->is_env == TRUE) || quotes == TRUE)
		{
			env_str[i] = add_env(env, quotes);
			if (!env_str[i])
				return (free_env_str(env_str), NULL);
			if (env_str[i] != NULL)
				i++;
		}
		env = env->next;
	}
	env_str[i] = NULL;
	return (env_str);
}

static int	env_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

static char	*add_env(t_env *env, int quotes)
{
	char	*env_str;

	if (env->name && env->is_env == TRUE)
	{
		env_str = ft_strjoin(env->name, "=");
		if (quotes == TRUE)
			env_str = ft_strjoin(env_str, "\"");
		if (env->value)
			env_str = ft_strjoin(env_str, env->value);
		if (quotes == TRUE)
			env_str = ft_strjoin(env_str, "\"");
		return (env_str);
	}
	return (env->name);
}

void	free_env_str(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}
