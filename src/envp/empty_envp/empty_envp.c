/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:18:36 by anrodri2          #+#    #+#             */
/*   Updated: 2023/08/03 20:55:13 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pwd(t_shell *shell)
{
	char	*buf;
	char	*copy_pwd;

	buf = NULL;
	buf = getcwd(buf, 0);
	if (!buf)
		malloc_err_exit(shell);
	copy_pwd = ft_strdup(buf);
	if (!copy_pwd)
		malloc_err_exit(shell);
	free(buf);
	return (copy_pwd);
}

t_env	*empty_envp(t_shell *shell)
{
	t_env	*new_env;
	char	*name;
	char	*pwd;

	pwd = get_pwd(shell);
	if (!pwd)
		return (NULL);
	name = ft_strdup("PWD");
	if (!name)
		malloc_err_exit(shell);
	new_env = env_create(name, pwd, TRUE);
	if (!new_env)
		return (NULL);
	return (new_env);
}
