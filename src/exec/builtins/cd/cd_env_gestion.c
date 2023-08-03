/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_env_gestion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 09:20:04 by anrodri2          #+#    #+#             */
/*   Updated: 2023/08/03 21:36:18 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cd_save_pwd(t_shell *shell)
{
	char	*buf;

	(void)shell;
	buf = NULL;
	buf = getcwd(buf, 0);
	if (!buf)
		return (NULL);
	return (buf);
}

void	old_pwd_save(t_env **env, char *saved_pwd)
{
	t_env	*tmp;
	char	*name;

	tmp = *env;
	while (tmp && tmp->name)
	{
		if (ft_strcmp(tmp->name, "OLDPWD") == 0)
		{
			free(tmp->value);
			tmp->value = saved_pwd;
			return ;
		}
		tmp = tmp->next;
	}
	name = ft_strdup("OLDPWD");
	if (!name)
		malloc_err_exit(NULL);
	if (envadd_elem(*env, name, saved_pwd, TRUE))
		malloc_err_exit(NULL);
}

void	update_pwd(t_env *env, t_shell *shell)
{
	char	*new_pwd;

	new_pwd = cd_save_pwd(shell);
	if (!new_pwd)
		malloc_err_exit(shell);
	while (env)
	{
		if (ft_strcmp(env->name, "PWD") == 0)
		{
			free(env->value);
			env->value = new_pwd;
			return ;
		}
		env = env->next;
	}
	free(new_pwd);
}
