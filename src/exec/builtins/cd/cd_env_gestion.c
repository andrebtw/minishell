/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_env_gestion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 09:20:04 by anrodri2          #+#    #+#             */
/*   Updated: 2023/07/25 15:59:13 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cd_save_pwd(void)
{
	char	*buf;
	char	*copy_pwd;

	buf = NULL;
	buf = getcwd(buf, 0);
	if (!buf)
		return (NULL);
	copy_pwd = ft_strdup(buf);
	if (!copy_pwd)
		return (NULL);
	free(buf);
	return (copy_pwd);
}

void	old_pwd_save(t_env **env, char *saved_pwd)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "OLDPWD") == 0)
		{
			free(tmp->value);
			tmp->value = saved_pwd;
			return ;
		}
		tmp = tmp->next;
	}
	if (envadd_elem(*env, "OLDPWD", saved_pwd, TRUE))
		malloc_err_exit(NULL);
}

void	update_pwd(t_env **env)
{
	t_env	*tmp;
	char	*new_pwd;

	tmp = *env;
	new_pwd = cd_save_pwd();
	if (!new_pwd)
		malloc_err_exit(NULL);
	while (tmp)
	{
		if (ft_strcmp(tmp->name, "PWD") == 0)
		{
			free(tmp->value);
			tmp->value = new_pwd;
			return ;
		}
		tmp = tmp->next;
	}
}
