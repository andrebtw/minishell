/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 09:55:09 by anrodri2          #+#    #+#             */
/*   Updated: 2023/05/09 20:56:46 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

int	empty_check(t_shell *shell, size_t i)
{
	while (shell->input[i])
	{
		if (shell->input[i] != ' ' && shell->input[i] != '\t')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	quotes_state_error(t_shell *shell, size_t i, int state)
{
	if (shell->input[i] == '\'' && state == SINGLE_QUOTE)
		return (NOT_INIT);
	if (shell->input[i] == '\"' && state == DOUBLE_QUOTE)
		return (NOT_INIT);
	if (shell->input[i] == '\"' && state == NOT_INIT)
		return (DOUBLE_QUOTE);
	if (shell->input[i] == '\'' && state == NOT_INIT)
		return (SINGLE_QUOTE);
	if (state == DOUBLE_QUOTE || state == SINGLE_QUOTE)
		return (state);
	return (NOT_INIT);
}

int	errors(t_shell *shell)
{
	size_t	i;
	int		state;

	i = 0;
	state = NOT_INIT;
	if (empty_check(shell, i))
		return (TRUE);
	if (pipe_check(shell, i, state))
		return (TRUE);
	if (quotes_check(shell, i, state))
		return (TRUE);
	if (redirections_check(shell, i, state))
		return (TRUE);
	// TODO: redirection errors
	return (FALSE);
}
