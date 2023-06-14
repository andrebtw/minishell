/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:18:36 by anrodri2          #+#    #+#             */
/*   Updated: 2023/06/13 09:27:17 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pwd(void)
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

t_env	*empty_envp(void)
{
	t_env	*new_env;
	char	*pwd;

	pwd = get_pwd();
	if (!pwd)
		return (NULL);
	new_env = env_create("PWD", pwd, TRUE);
	if (envadd_elem(new_env, "SHLVL", "1", TRUE))
		return (NULL);
	if (!new_env)
		return (NULL);
	return (new_env);
}