/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 09:55:09 by anrodri2          #+#    #+#             */
/*   Updated: 2023/05/04 11:46:03 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"
#define PIPE_ERR_MSG "🗿: syntax error near unexpected token `|'\n"

int	pipe_check(t_shell *shell, size_t i)
{
	(void)shell;
	(void)i;
	return (TRUE);
}

int	errors(t_shell *shell)
{
	size_t	i;

	i = 0;
	if (pipe_check(shell, i))
		return (ft_putstr_fd(PIPE_ERR_MSG, 2), TRUE);
	return (FALSE);
}
