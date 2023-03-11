/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:25:20 by anrodri2          #+#    #+#             */
/*   Updated: 2023/03/11 16:57:17 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	clean_exit(t_shell *shell)
{
	if (shell->input)
		free(shell->input);
	exit(EXIT_SUCCESS);
}

void	malloc_err_exit(t_shell *shell)
{
	if (shell->input)
		free(shell->input);
	ft_printf(MSG_ERR_MALLOC, KRED, KNORMAL);
	exit(ERR_MALLOC);
}
