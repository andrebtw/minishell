/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 00:10:08 by anrodri2          #+#    #+#             */
/*   Updated: 2023/08/02 00:17:40 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quotes_gestion(t_shell *shell, size_t *i, int *state);

void	add_to_char(t_shell *shell, size_t *i, int *state)
{
	env_gestion(shell, i, state);
	if (!shell->input[*i])
		return ;
	if (*state == NOT_INIT && !ft_strchr(" \t<>|\'\"", shell->input[*i]))
	{
		shell->parsing.current_str = ft_strjoin_free_char(
				shell->parsing.current_str, shell->input[*i], 1);
		if (!shell->parsing.current_str)
			malloc_err_exit(shell);
		return ;
	}
	separators_split(shell, i, state);
	quotes_gestion(shell, i, state);
}

void	redirect_quotes_add(t_shell *shell, size_t *i, int *state)
{
	if (*state == REDIRECT_SINGLE_QUOTE)
	{
		if (shell->input[*i] != '\'')
		{
			shell->parsing.current_redirect_str = ft_strjoin_free_char(
					shell->parsing.current_redirect_str, shell->input[*i], 1);
			if (!shell->parsing.current_redirect_str)
				malloc_err_exit(shell);
		}
		return ;
	}
	if (*state == REDIRECT_DOUBLE_QUOTE)
	{
		if (shell->input[*i] != '\"')
		{
			shell->parsing.current_redirect_str = ft_strjoin_free_char(
					shell->parsing.current_redirect_str, shell->input[*i], 1);
			if (!shell->parsing.current_redirect_str)
				malloc_err_exit(shell);
		}
		return ;
	}
}

void	add_to_char_redirect(t_shell *shell, size_t *i, int *state)
{
	env_gestion(shell, i, state);
	if (!shell->input[*i])
		return ;
	if (*state == REDIRECT && !ft_strchr("<>|\'\"", shell->input[*i]))
	{
		shell->parsing.current_redirect_str = ft_strjoin_free_char(
				shell->parsing.current_redirect_str, shell->input[*i], 1);
		if (!shell->parsing.current_redirect_str)
			malloc_err_exit(shell);
		return ;
	}
	separators_split(shell, i, state);
	redirect_quotes_add(shell, i, state);
}
