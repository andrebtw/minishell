/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:49:29 by anrodri2          #+#    #+#             */
/*   Updated: 2023/05/12 17:09:47 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

void	free_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;

	tmp = *cmd;
	free(*cmd);
	while (tmp->next)
	{
		// free(tmp->in_out_code);
		// ft_free_tab(tmp->content);
		// ft_free_tab(tmp->in_out);
		// free(tmp);
		tmp = tmp->next;
	}
}

void	cmd_free(t_shell *shell)
{
	(void)shell;
}
