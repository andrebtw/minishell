/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 < anrodri2@student.42lyon.fr >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:35:38 by codespace         #+#    #+#             */
/*   Updated: 2023/04/03 17:00:03 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	print_list(t_cmd *lst)
{
	while (lst)
	{
		ft_printf("-----------------------");
		lst = lst->next;
	}
}

void	debug_print(t_shell *shell)
{
	print_list(shell->command);
}
