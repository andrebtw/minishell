/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 04:40:31 by anrodri2          #+#    #+#             */
/*   Updated: 2023/08/02 00:11:07 by anrodri2         ###   ########.fr       */
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

void	split_shell_init(t_shell *shell)
{
	shell->parsing.current_str = NULL;
	shell->parsing.current_tab = NULL;
	shell->parsing.current_redirect_tab = NULL;
	shell->parsing.current_redirect_str = NULL;
	shell->parsing.current_in_out_code = NULL;
	shell->parsing.is_heredoc = FALSE;
	shell->parsing.error_code_parsing = FALSE;
	shell->parsing.quote_end = FALSE;
}
