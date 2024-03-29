/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_to_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:56:00 by mthibaul          #+#    #+#             */
/*   Updated: 2023/08/03 20:43:02 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*envp_to_list(char **envp)
{
	t_env	*env;

	env = env_create(find_name(*envp), find_value(*envp), TRUE);
	if (!env)
		return (print_error(ERR_MALLOC_MSG), exit(ENOMEM), NULL);
	envp++;
	while (*envp)
	{
		if ((envadd_elem(env, find_name(*envp), find_value(*envp), TRUE)) > 0)
			return (free_env(env), NULL);
		envp++;
	}
	return (env);
}

t_env	*env_create(char *name, char *value, int is_env)
{
	t_env	*elem;

	elem = (t_env *) malloc(sizeof(t_env));
	if (!elem || !name)
		return (free(name), free(value), \
		print_error(ERR_MALLOC_MSG), exit(ENOMEM), NULL);
	elem->name = name;
	elem->value = value;
	elem->is_env = is_env;
	elem->next = NULL;
	return (elem);
}

int	envadd_elem(t_env *env, char *name, char *value, int is_env)
{
	t_env	*new;

	if (!env->name)
	{
		env->name = name;
		env->value = value;
		return (0);
	}
	new = env_create(name, value, is_env);
	if (!new)
		return (1);
	envadd_back(env, new);
	return (0);
}

void	envadd_back(t_env *env, t_env *new)
{
	if (!env)
	{
		env = new;
		return ;
	}
	while (env->next)
		env = env->next;
	env->next = new;
}
