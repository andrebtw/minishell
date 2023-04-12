/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_to_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthibaul <mthibaul@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:56:00 by mthibaul          #+#    #+#             */
/*   Updated: 2023/04/06 11:56:00 by mthibaul         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_env	*env_create(char *name, char *value);
int		envadd_elem(t_env **env, char *name, char *value);
void	envadd_back(t_env **env, t_env *new);

t_env	**envp_to_list(char **envp)
{
	t_env	*env;

	env = env_create(find_name(*envp), find_value(*envp));
	if (!env)
		return (NULL);
	envp++;
	while (envp)
	{
		if (envadd_elem(&env, find_name(*envp), find_value(*envp)) > 0)
			return (free_env(env), NULL);
		envp++;
	}
	return (&env);
}

t_env	*env_create(char *name, char *value)
{
	t_env	*elem;

	elem = (t_env *) malloc(sizeof(t_env));
	if (!elem || !name || !value)
		return (free(name), free(value), NULL);
	elem->name = name;
	elem->value = value;
	elem->next = NULL;
	return (elem);
}

int envadd_elem(t_env **env, char *name, char *value)
{
	t_env *new;

	new = env_create(name, value);
	if (!new)
		return (1);
	envadd_back(env, new);
	return (0);
}

void envadd_back(t_env **env, t_env *new)
{
	if (!(*env))
	{
		*env = new;
		return ;
	}
	while ((*env)->next)
		*env = (*env)->next;
	(*env)->next = new;
}
