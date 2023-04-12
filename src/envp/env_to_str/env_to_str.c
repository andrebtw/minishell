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

int env_size(t_env *env);

char **env_to_str(t_env *env)
{
	char **env_str;

	env_str = malloc(sizeof(char *) * env_size(env));
	if (!env_str)
		return (NULL);

}

int env_size(t_env *env)
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