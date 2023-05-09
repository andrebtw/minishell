/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:39:41 by anrodri2          #+#    #+#             */
/*   Updated: 2023/05/09 20:45:55 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

int	quotes_check(t_shell *shell, size_t i, int state)
{
	while (shell->input[i])
	{
		state = quotes_state_error(shell, i, state);
		i++;
	}
	if (state == SINGLE_QUOTE)
	{
		ft_putstr_fd(SINGLEQUOTE_ERR_MSG, 2);
		return (TRUE);
	}
	if (state == DOUBLE_QUOTE)
	{
		ft_putstr_fd(DOUBLEQUOTE_ERR_MSG, 2);
		return (TRUE);
	}
	return (FALSE);
}
