/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 15:35:38 by anrodri2          #+#    #+#             */
/*   Updated: 2023/07/20 12:01:20 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(t_cmd *lst)
{
	size_t	i;

	while (lst)
	{
		i = 0;
		ft_printf("\n------------\n");
		ft_printf("| CONTENT : ");
		if (!lst->content)
		{
			ft_printf("EMPTY");
		}
		else
		{
			while (lst->content[i])
			{
				ft_printf("%s,", lst->content[i]);
				i++;
			}
		}
		i = 0;
		ft_printf("\n| REDIRECTIONS : ");
		if (!lst->in_out)
		{
			ft_printf("EMPTY\n");
		}
		else if (!lst->in_out[i])
		{
			ft_printf("EMPTY\n");
		}
		else
		{
			while (lst->in_out[i])
			{
				ft_printf("%s:", lst->in_out[i]);
				if (lst->in_out_code[i] == IS_IN)
					ft_printf("IN,\n");
				if (lst->in_out_code[i] == IS_OUT)
					ft_printf("OUT,\n");
				if (lst->in_out_code[i] == IS_OUT_APPEND)
					ft_printf("OUT APPEND,\n");
				if (lst->in_out_code[i] == IS_HEREDOC)
					ft_printf("HEREDOC,\n");
				i++;
			}
		}
		ft_printf("| IS BUILT IN : ");
		if (lst->type == IS_CMD)
			ft_printf("False");
		else
			ft_printf("True");
		lst = lst->next;
	}
	ft_printf("\n------------\n");
}

void	debug_print(t_shell *shell)
{
	print_list(shell->command);
}
