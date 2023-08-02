/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_g_code.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 22:07:13 by anrodri2          #+#    #+#             */
/*   Updated: 2023/08/02 22:43:55 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_code;

void	pipes_g_code(int ret_value)
{
	if (WEXITSTATUS(ret_value) == 130 || \
	WEXITSTATUS(ret_value) == 131)
		g_code = WEXITSTATUS(ret_value);
	else if (WEXITSTATUS(ret_value))
		g_code = WEXITSTATUS(ret_value) % 128;
}
