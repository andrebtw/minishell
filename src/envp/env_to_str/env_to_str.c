/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthibaul <mthibaul@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:13:00 by mthibaul          #+#    #+#             */
/*   Updated: 2023/04/12 12:13:00 by mthibaul         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int		env_size(t_env *env);
int		add_env(t_env *env, char *env_str);
void	free_env_str(char **env_str);

char **env_to_str(t_env *env)
{
	char	**env_str;
	int		i;

	env_str = malloc(sizeof(char *) * env_size(env));
	if (!env_str)
		return (NULL);
	i = 0;
	while (env)
	{
		if (add_env(env,  env_str[i]) > 0)
			return (free_env_str(env_str), NULL);
		env++;
		i++;
	}
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

int	add_env(t_env *env, char *env_str)
{
	int len;

	len = (int) ft_strlen(env->name) + (int) ft_strlen(env->value) + 2;
	env_str = malloc(sizeof(char) * len);
	if (!env_str)
		return (1);
	ft_strcat(env_str, env->name);
	ft_strcat(env_str, "=");
	ft_strcat(env_str, env->value);
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