/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 04:40:31 by anrodri2          #+#    #+#             */
/*   Updated: 2023/07/11 04:43:34 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_gestion(t_shell *shell, size_t *i, int *state);
void	separators_split(t_shell *shell, size_t *i, int *state);

void	quotes_gestion(t_shell *shell, size_t *i, int *state)
{
	if (*state == SINGLE_QUOTE)
	{
		if (shell->input[*i] != '\'')
			shell->parsing.current_str = ft_strjoin_free_char(
					shell->parsing.current_str, shell->input[*i], 1);
		if (!shell->parsing.current_str)
			malloc_err_exit(shell);
		return ;
	}
	if (*state == DOUBLE_QUOTE)
	{
		if (shell->input[*i] != '\"')
			shell->parsing.current_str = ft_strjoin_free_char(
					shell->parsing.current_str, shell->input[*i], 1);
		if (!shell->parsing.current_str)
			malloc_err_exit(shell);
		return ;
	}
}

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
		if (ft_strchr("><", shell->input[*i + 1]))
		{
			shell->parsing.current_str = ft_strjoin_free_char(
					shell->parsing.current_str, SEPARATOR, 1);
			if (!shell->parsing.current_str)
				malloc_err_exit(shell);
		}
		return ;
	}
	separators_split(shell, i, state);
	quotes_gestion(shell, i, state);
}
