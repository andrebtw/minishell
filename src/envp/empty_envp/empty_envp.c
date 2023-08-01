/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 15:18:36 by anrodri2          #+#    #+#             */
/*   Updated: 2023/07/24 14:47:12 by anrodri2         ###   ########.fr       */
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
	char	*pwd;

	pwd = get_pwd(shell);
	if (!pwd)
		return (NULL);
	new_env = env_create(ft_strdup("PWD"), pwd, TRUE);
	if (envadd_elem(new_env, ft_strdup("SHLVL"), ft_strdup("1"), TRUE))
		return (NULL);
	if (!new_env)
		return (NULL);
	return (new_env);
}
