/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:56:15 by anrodri2          #+#    #+#             */
/*   Updated: 2023/05/10 01:17:26 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

int	check_pipe(t_shell *shell, size_t i)
{
	if (shell->input[i] == '|')
	{
		if (shell->input[i + 1] == '|')
			return (ft_putstr_fd(PIPE_ERR_MSG2, 2), TRUE);
		return (ft_putstr_fd(PIPE_ERR_MSG, 2), TRUE);
	}
	return (FALSE);
}

int	output_check(t_shell *shell, size_t i)
{
	i++;
	while (shell->input[i] && ft_strchr(" \t", shell->input[i]))
		i++;
	if (!shell->input[i])
		return (ft_putstr_fd(REDIRECT_NOEND_ERR_MSG, 2), TRUE);
	if (check_pipe(shell, i))
		return (TRUE);
	return (FALSE);
}

int	input_check(t_shell *shell, size_t i)
{
	i++;
	while (shell->input[i] && ft_strchr(" \t", shell->input[i]))
		i++;
	if (!shell->input[i])
		return (ft_putstr_fd(REDIRECT_NOEND_ERR_MSG, 2), TRUE);
	if (check_pipe(shell, i))
		return (TRUE);
	return (FALSE);
}

int	redirections_check(t_shell *shell, size_t i, int state)
{
	while (shell->input[i])
	{
		state = quotes_state_error(shell, i, state);
		if (state == NOT_INIT)
		{
			if (shell->input[i] == '>')
			{
				if (output_check(shell, i))
					return (TRUE);
			}
			if (shell->input[i] == '<')
			{
				if (input_check(shell, i))
					return (TRUE);
			}
		}
		i++;
	}
	return (FALSE);
}
