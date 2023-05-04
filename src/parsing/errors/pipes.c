/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:02:54 by anrodri2          #+#    #+#             */
/*   Updated: 2023/05/04 13:05:18 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

int	pipe_check(t_shell *shell, size_t i)
{
	while (shell->input[i] == ' ' || shell->input[i] == '\t')
		i++;
	if (shell->input[i] == '|' && shell->input[i + 1] == '|')
		return (ft_putstr_fd(PIPE_ERR_MSG2, 2), TRUE);
	if (shell->input[i] == '|')
		return (ft_putstr_fd(PIPE_ERR_MSG, 2), TRUE);
	return (FALSE);
}
