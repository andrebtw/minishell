/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:25:00 by mthibaul          #+#    #+#             */
/*   Updated: 2023/08/03 21:14:20 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env && env->name)
	{
		tmp = env->next;
		free(env->name);
		free(env->value);
		free(env);
		env = tmp;
	}
}
