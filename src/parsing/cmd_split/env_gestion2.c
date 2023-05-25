/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_gestion2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:46:33 by anrodri2          #+#    #+#             */
/*   Updated: 2023/05/25 11:52:38 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

void	split_space_env(t_shell *shell, size_t *i, int *state)
{
	(void)state;
	if (shell->input[*i] && ft_strchr(" \t", shell->input[*i + 1]))
	{
		shell->parsing.current_str = ft_strjoin_free_char(shell->parsing.current_str, SEPARATOR, 1);
		if (!shell->parsing.current_str)
			malloc_err_exit(shell);
	}
}

char	*is_in_env(t_shell *shell, t_env **env, char *env_name)
{
	t_env	*tmp;
	char	*r_string;

	tmp = *env;
	while (tmp->next)
	{
		if (!ft_strcmp(tmp->name, env_name))
		{
			r_string = ft_strdup(tmp->value);
			if (!r_string)
			{
				free(env_name);
				return (malloc_err_exit(shell), NULL);
			}
			return (r_string);
		}
		tmp = tmp->next;
	}
	if (!ft_strcmp(tmp->name, env_name))
	{
		r_string = ft_strdup(tmp->value);
			if (!r_string)
			{
				free(env_name);
				return (malloc_err_exit(shell), NULL);
			}
			return (r_string);
	}
	return (NULL);
}

void	find_env(t_shell *shell, size_t *i, int *state, char *env_name)
{
	char	*env_value;

	(void)state;
	(void)i;
	(void)shell;
	env_value = is_in_env(shell, &shell->env, env_name);
	if (!env_value)
		return ;
	free(env_name);
	shell->parsing.current_str = ft_strjoin_free(shell->parsing.current_str, env_value, 1, 1);
	if (!shell->parsing.current_str)
		malloc_err_exit(shell);
}
