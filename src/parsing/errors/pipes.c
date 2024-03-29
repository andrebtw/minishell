/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:02:54 by anrodri2          #+#    #+#             */
/*   Updated: 2023/05/09 20:00:50 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

int	check_if_more_pipes(t_shell *shell, size_t i)
{
	while (shell->input[i] && ft_strchr(" \t", shell->input[i]))
		i++;
	if (!shell->input[i])
		return (ft_putstr_fd(PIPE_ERR_MSG, 2), TRUE);
	if (shell->input[i] == '|')
		return (ft_putstr_fd(PIPE_ERR_MSG2, 2), TRUE);
	ft_putstr_fd(PIPE_ERR_MSG, 2);
	return (TRUE);
}

int	pipe_loop(t_shell *shell, size_t i, int state)
{
	while (shell->input[i])
	{
		state = quotes_state_error(shell, i, state);
		if (state == NOT_INIT)
		{
			if (ft_strchr("|", shell->input[i]))
			{
				i++;
				while (shell->input[i] && ft_strchr(" \t", shell->input[i]))
					i++;
				if (shell->input[i] == '|')
					return (check_if_more_pipes(shell, i));
				if (!shell->input[i])
					return (ft_putstr_fd(PIPE_ERR_MSG, 2), TRUE);
			}
		}
		i++;
	}
	return (FALSE);
}

int	pipe_check(t_shell *shell, size_t i, int state)
{
	(void)state;
	while (shell->input[i] == ' ' || shell->input[i] == '\t')
		i++;
	if (shell->input[i] == '|')
	{
		if (shell->input[i + 1] == '|')
			return (ft_putstr_fd(PIPE_ERR_MSG2, 2), TRUE);
		i++;
		if (!ft_strchr(" \t", shell->input[i]))
			return (ft_putstr_fd(PIPE_ERR_MSG, 2), TRUE);
		while (shell->input[i] && ft_strchr(" \t", shell->input[i]))
			i++;
		if (shell->input[i] == '|')
			return (ft_putstr_fd(PIPE_ERR_MSG2, 2), TRUE);
		return (ft_putstr_fd(PIPE_ERR_MSG, 2), TRUE);
	}
	i = 0;
	if (pipe_loop(shell, i, state))
		return (TRUE);
	return (FALSE);
}
