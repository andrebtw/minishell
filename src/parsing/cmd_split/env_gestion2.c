/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_gestion2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:46:33 by anrodri2          #+#    #+#             */
/*   Updated: 2023/08/01 22:26:05 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

void	split_space_env(t_shell *shell, size_t *i, int *state)
{
	if (shell->input[*i] && ft_strchr(" \t", shell->input[*i]))
	{
		if (*state == NOT_INIT)
		{
			shell->parsing.current_str = ft_strjoin_free_char(\
			shell->parsing.current_str, SEPARATOR, 1);
			if (!shell->parsing.current_str)
				malloc_err_exit(shell);
		}
		else if (*state == REDIRECT)
		{
			shell->parsing.current_redirect_str = ft_strjoin_free_char(\
			shell->parsing.current_redirect_str, SEPARATOR, 1);
			if (!shell->parsing.current_redirect_str)
				malloc_err_exit(shell);
		}
	}
}

char	*is_in_env(t_shell *shell, t_env **env, char *env_name, int *state)
{
	t_env	*tmp;
	char	*r_string;

	(void)state;
	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, env_name) && tmp->value)
		{
			r_string = ft_strdup(tmp->value);
			if (!r_string)
			{
				ft_free_char(&env_name);
				return (malloc_err_exit(shell), NULL);
			}
			return (r_string);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

int	find_env(t_shell *shell, int *state, char *env_name)
{
	char	*env_value;

	env_value = is_in_env(shell, &shell->env, env_name, state);
	if (*state > REDIRECT)
		ft_free_char(&env_name);
	if (!env_value)
		return (env_name = NULL, FALSE);
	env_value = env_spaces(env_value);
	if (!env_value)
		malloc_err_exit(shell);
	if (*state >= SPACE_SEP)
	{
		shell->parsing.current_str = ft_strjoin_free(\
		shell->parsing.current_str, env_value, 1, 1);
		if (!shell->parsing.current_str)
			malloc_err_exit(shell);
	}
	else
	{
		shell->parsing.current_redirect_str = ft_strjoin_free(\
		shell->parsing.current_redirect_str, env_value, 1, 1);
		if (!shell->parsing.current_redirect_str)
			malloc_err_exit(shell);
	}
	return (env_name = NULL, TRUE);
}

void	here_doc_check_quotes(t_shell *shell, size_t *i, int *state)
{
	if (*state == REDIRECT)
	{
		shell->parsing.current_redirect_str = ft_strjoin_free_char(
				shell->parsing.current_redirect_str, SEPARATOR, 1);
		if (!shell->parsing.current_redirect_str)
			malloc_err_exit(shell);
	}
	if (*state == REDIRECT_SINGLE_QUOTE && shell->input[*i] == '\'')
	{
		shell->parsing.current_redirect_str = ft_strjoin_free_char(
				shell->parsing.current_redirect_str, SEPARATOR, 1);
		if (!shell->parsing.current_redirect_str)
			malloc_err_exit(shell);
	}
	if (*state == REDIRECT_DOUBLE_QUOTE && shell->input[*i] == '\"')
	{
		shell->parsing.current_redirect_str = ft_strjoin_free_char(
				shell->parsing.current_redirect_str, SEPARATOR, 1);
		if (!shell->parsing.current_redirect_str)
			malloc_err_exit(shell);
	}
}

int	heredoc_env_remove(t_shell *shell, size_t *i, int *state)
{
	(void)*state;
	if (shell->input[*i] != '$')
		return (FALSE);
	if (!shell->parsing.is_heredoc)
		return (FALSE);
	while (shell->input[*i] && !ft_strchr(" \t<>|", shell->input[*i]))
	{
		shell->parsing.current_redirect_str = ft_strjoin_free_char(\
		shell->parsing.current_redirect_str, shell->input[*i], 1);
		if (!shell->parsing.current_redirect_str)
			malloc_err_exit(shell);
		*i = *i + 1;
	}
	here_doc_check_quotes(shell, i, state);
	shell->parsing.is_heredoc = FALSE;
	return (TRUE);
}
