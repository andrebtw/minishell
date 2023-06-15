/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 15:16:41 by anrodri2          #+#    #+#             */
/*   Updated: 2023/06/15 09:45:02 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

char	*malloc_int_code(t_shell *shell, char redirect)
{
	char	*new_str;

	if (!shell->parsing.current_in_out_code)
	{
		new_str = ft_strdup("");
		if (!new_str)
			malloc_err_exit(shell);
		new_str = ft_strjoin_free_char(new_str, redirect, 1);
		if (!new_str)
			malloc_err_exit(shell);
		return (new_str);
	}
	new_str = ft_strjoin_free_char(\
	shell->parsing.current_in_out_code, redirect, 1);
	if (!new_str)
	{
		free(shell->parsing.current_in_out_code);
		malloc_err_exit(shell);
	}
	return (new_str);
}

void	heredoc_append(t_shell *shell, size_t *i, int *state)
{
	if ((*state == NOT_INIT && shell->input[*i] == '>') \
	&& shell->input[*i + 1] == '>')
	{
		shell->parsing.current_in_out_code = malloc_int_code(\
		shell, IS_OUT_APPEND);
		*state = REDIRECT;
		*i = *i + 2;
		while (ft_strchr(" \t", shell->input[*i]))
			*i = *i + 1;
		*i = *i - 1;
	}
	if ((*state == NOT_INIT && shell->input[*i] == '<') \
	&& shell->input[*i + 1] == '<')
	{
		shell->parsing.is_heredoc = TRUE;
		shell->parsing.current_in_out_code = malloc_int_code(shell, IS_HEREDOC);
		*state = REDIRECT;
		*i = *i + 2;
		while (ft_strchr(" \t", shell->input[*i]))
			*i = *i + 1;
		*i = *i - 1;
	}
}

void	separators_split(t_shell *shell, size_t *i, int *state)
{
	if (shell->parsing.is_heredoc)
		shell->parsing.is_heredoc = FALSE;
	if (*state == NOT_INIT && shell->input[*i] == '|')
		end_found(shell, *i);
	heredoc_append(shell, i, state);
	if (*state == NOT_INIT && shell->input[*i] == '>')
	{
		shell->parsing.current_in_out_code = malloc_int_code(shell, IS_OUT);
		*state = REDIRECT;
		*i = *i + 1;
		while (ft_strchr(" \t", shell->input[*i]))
			*i = *i + 1;
		*i = *i - 1;
	}
	if (*state == NOT_INIT && shell->input[*i] == '<')
	{
		shell->parsing.current_in_out_code = malloc_int_code(shell, IS_IN);
		*state = REDIRECT;
		*i = *i + 1;
		while (ft_strchr(" \t", shell->input[*i]))
			*i = *i + 1;
		*i = *i - 1;
	}
}
