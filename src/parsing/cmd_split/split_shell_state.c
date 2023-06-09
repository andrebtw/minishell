/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell_state.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 11:44:17 by anrodri2          #+#    #+#             */
/*   Updated: 2023/06/09 08:13:25 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

int	quotes_state_redirect(t_shell *shell, size_t i, int state)
{
	if (state == REDIRECT && ft_strchr(" \t<>|", shell->input[i]))
	{
		shell->parsing.current_redirect_str = ft_strjoin_free_char(
				shell->parsing.current_redirect_str, SEPARATOR, 1);
		if (!shell->parsing.current_redirect_str)
			malloc_err_exit(shell);
		return (NOT_INIT);
	}
	if (shell->input[i] == '\'' && state == REDIRECT)
		return (REDIRECT_SINGLE_QUOTE);
	if (shell->input[i] == '\"' && state == REDIRECT)
		return (REDIRECT_DOUBLE_QUOTE);
	if (shell->input[i] == '\'' && state == REDIRECT_SINGLE_QUOTE)
		return (shell->parsing.quote_end = TRUE, REDIRECT);
	if (shell->input[i] == '\"' && state == REDIRECT_DOUBLE_QUOTE)
		return (shell->parsing.quote_end = TRUE, REDIRECT);
	if (state == REDIRECT_DOUBLE_QUOTE || state == REDIRECT_SINGLE_QUOTE)
		return (state);
	return (REDIRECT);
}

int	quotes_state(t_shell *shell, size_t i, int state)
{
	if (state == SPACE_SEP && ft_strchr(" \t", shell->input[i]))
		return (SPACE_SEP);
	if (state == NOT_INIT && ft_strchr(" \t", shell->input[i]))
	{
		shell->parsing.current_str = ft_strjoin_free_char(
				shell->parsing.current_str, SEPARATOR, 1);
		if (!shell->parsing.current_str)
			malloc_err_exit(shell);
		return (SPACE_SEP);
	}
	if (shell->input[i] == '\'' && state == SINGLE_QUOTE)
		return (shell->parsing.quote_end = TRUE, NOT_INIT);
	if ((shell->input[i] == '\'' && state == NOT_INIT)
		|| (shell->input[i] == '\'' && state == SPACE_SEP))
		return (SINGLE_QUOTE);
	if (shell->input[i] == '\"' && state == DOUBLE_QUOTE)
		return (shell->parsing.quote_end = TRUE, NOT_INIT);
	if ((shell->input[i] == '\"' && state == NOT_INIT)
		|| (shell->input[i] == '\"' && state == SPACE_SEP))
		return (DOUBLE_QUOTE);
	if (state == DOUBLE_QUOTE || state == SINGLE_QUOTE)
		return (state);
	return (NOT_INIT);
}
