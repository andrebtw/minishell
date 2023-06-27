/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 08:42:06 by anrodri2          #+#    #+#             */
/*   Updated: 2023/06/26 18:33:28 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

int		quotes_state_redirect(t_shell *shell, size_t i, int state);
int		quotes_state(t_shell *shell, size_t i, int state);
void	add_to_char_redirect(t_shell *shell, size_t *i, int *state);
void	add_to_char(t_shell *shell, size_t *i, int *state);

void	split_shell_loop(t_shell *shell, size_t i, int state)
{
	while (shell->input[i])
	{
		if (!shell->parsing.current_in_out_code)
			shell->parsing.current_in_out_code = ft_strdup("");
		if (!shell->parsing.current_in_out_code)
			malloc_err_exit(shell);
		empty_args(shell, &i, state);
		shell->parsing.quote_end = FALSE;
		if (state > REDIRECT)
		{
			state = quotes_state(shell, i, state);
			add_to_char(shell, &i, &state);
		}
		else
		{
			state = quotes_state_redirect(shell, i, state);
			add_to_char_redirect(shell, &i, &state);
		}
		if (shell->input[i])
			i++;
		if (shell->parsing.error_code_parsing == ERR_ENV_EMPTY_REDIRECT)
			break ;
	}
}
