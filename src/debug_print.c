/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:35:38 by anrodri2          #+#    #+#             */
/*   Updated: 2023/04/19 15:19:21 by anrodri2         ###   ########.fr       */
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
		if (!lst->content[i])
		{
			ft_printf("EMPTY");
		}
		else
		{
			while (lst->content[i])
			{
				ft_printf("%s ", lst->content[i]);
				i++;
			}
		}
		i = 0;
		ft_printf("\n| REDIRECTIONS : ");
		if (!lst->in_out[i])
		{
			ft_printf("EMPTY");
		}
		else
		{
			while (lst->in_out[i])
			{
				ft_printf("%s ", lst->in_out[i]);
				i++;
			}
		}
		lst = lst->next;
		ft_printf("\n");
	}
}

void	debug_print(t_shell *shell)
{
	print_list(shell->command);
}
