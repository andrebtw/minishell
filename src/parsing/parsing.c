/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:03:17 by anrodri2          #+#    #+#             */
/*   Updated: 2023/03/11 18:44:49 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

void	parsing(t_shell *shell)
{
	char	**tab;

	tab = ft_split(shell->input, ' ');
	if (!tab)
		malloc_err_exit(shell);
	
}
