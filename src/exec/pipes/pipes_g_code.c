/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_g_code.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 22:07:13 by anrodri2          #+#    #+#             */
/*   Updated: 2023/08/03 00:23:37 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_code;

void	pipes_g_code(t_shell *shell, int ret_value, int is_last)
{
	if (WEXITSTATUS(ret_value) == 130 || \
	WEXITSTATUS(ret_value) == 131)
	{
		if (!shell->is_signal)
		{
			if (WEXITSTATUS(ret_value) == 131)
				ft_printf("Quit\n");
			else if (WEXITSTATUS(ret_value) == 130)
				ft_printf("\n");
		}
		shell->is_signal = TRUE;
		g_code = WEXITSTATUS(ret_value);
	}
	else if ((WEXITSTATUS(ret_value) && is_last) && !shell->is_signal)
		g_code = WEXITSTATUS(ret_value) % 128;
}
