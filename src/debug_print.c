/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:35:38 by anrodri2          #+#    #+#             */
/*   Updated: 2023/04/04 20:50:39 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	print_list(t_cmd *lst)
{
	size_t	i;

	while (lst)
	{
		i = 0;
		ft_printf("------------\n");
		ft_printf("| TYPE    : %d\n", lst->type);
		ft_printf("| CONTENT : ");
		while (lst->content[i])
		{
			ft_printf("%s ", lst->content[i]);
			i++;
		}
		lst = lst->next;
		ft_printf("\n------------\n");
	}
}

void	debug_print(t_shell *shell)
{
	print_list(shell->command);
}
