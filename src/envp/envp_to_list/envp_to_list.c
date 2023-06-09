/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_to_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 11:56:00 by mthibaul          #+#    #+#             */
/*   Updated: 2023/05/06 17:47:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

#include "../../../incl/minishell.h"

t_env   *envp_to_list(char **envp)
{
	t_env	*env;
	int i;

	env = env_create(find_name(*envp), find_value(*envp));
	if (!env)
		return (NULL);
	envp++;
	while (*envp)
	{
		if ((i = envadd_elem(env, find_name(*envp), find_value(*envp))) > 0)
			return (free_env(env), printf("%d\n", i), NULL);
		envp++;
	}
	return (env);
}

t_env   *env_create(char *name, char *value)
{
        t_env   *elem;

	elem = (t_env *) malloc(sizeof(t_env));
	if (!elem || !name)
		return (free(name), free(value), NULL);
	elem->name = name;
	elem->value = value;
	elem->next = NULL;
	return (elem);
}

int envadd_elem(t_env *env, char *name, char *value)
{
        t_env *new;

        new = env_create(name, value);
        if (!new)
                return (1);
        envadd_back(env, new);
        return (0);
}

void envadd_back(t_env *env, t_env *new)
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