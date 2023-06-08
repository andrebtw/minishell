/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:27:37 by anrodri2          #+#    #+#             */
/*   Updated: 2023/06/08 12:42:37 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

void	add_separator(t_shell *shell)
{
	shell->parsing.current_str = ft_strjoin_free_char(
			shell->parsing.current_str, SEPARATOR, 1);
	if (!shell->parsing.current_str)
		malloc_err_exit(shell);
	shell->parsing.current_str = ft_strjoin_free_char(
			shell->parsing.current_str, EMPTY_SPACE, 1);
	if (!shell->parsing.current_str)
		malloc_err_exit(shell);
	shell->parsing.current_str = ft_strjoin_free_char(
			shell->parsing.current_str, SEPARATOR, 1);
	if (!shell->parsing.current_str)
		malloc_err_exit(shell);
}

void	add_separator_redirect(t_shell *shell)
{
	shell->parsing.current_redirect_str = ft_strjoin_free_char(
			shell->parsing.current_redirect_str, SEPARATOR, 1);
	if (!shell->parsing.current_redirect_str)
		malloc_err_exit(shell);
	shell->parsing.current_redirect_str = ft_strjoin_free_char(
			shell->parsing.current_redirect_str, EMPTY_SPACE, 1);
	if (!shell->parsing.current_redirect_str)
		malloc_err_exit(shell);
	shell->parsing.current_redirect_str = ft_strjoin_free_char(
			shell->parsing.current_redirect_str, SEPARATOR, 1);
	if (!shell->parsing.current_redirect_str)
		malloc_err_exit(shell);
}

void	check_quotes(t_shell *shell, size_t *i, int is_redirect)
{
	if (shell->input[*i] == '\"' && shell->input[*i + 1] == '\"')
	{
		*i = *i + 2;
		if ((!shell->input[*i] || !ft_strchr("\'\"", shell->input[*i])) &&
			(shell->parsing.quote_end == FALSE && ft_strchr(" \t", shell->input[*i])))
		{
			if (is_redirect)
				add_separator_redirect(shell);
			else
				add_separator(shell);
		}
	}
	if (shell->input[*i] == '\'' && shell->input[*i + 1] == '\'')
	{
		*i = *i + 2;
		if ((!shell->input[*i] || !ft_strchr("\'\"", shell->input[*i])) &&
			(shell->parsing.quote_end == FALSE && ft_strchr(" \t", shell->input[*i])))
		{
			if (is_redirect)
				add_separator_redirect(shell);
			else
				add_separator(shell);
		}
	}
}

void	empty_args(t_shell *shell, size_t *i, int state)
{
	int		quotes_loop;
	size_t	saved_index;

	quotes_loop = NOT_INIT;
	while (quotes_loop != FALSE)
	{
		saved_index = *i;
		if (state == NOT_INIT || state == SPACE_SEP)
			check_quotes(shell, i, FALSE);
		if (state == REDIRECT || state == REDIRECT_END)
			check_quotes(shell, i, TRUE);
		quotes_loop = TRUE;
		if (saved_index == *i)
			quotes_loop = FALSE;
	}
}
