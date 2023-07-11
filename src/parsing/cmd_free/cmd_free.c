/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 16:49:29 by anrodri2          #+#    #+#             */
/*   Updated: 2023/07/11 03:47:22 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

void	free_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;
	t_cmd	*tmp2;

	tmp = *cmd;
	while (tmp)
	{
		tmp2 = tmp;
		ft_free_tab(tmp->content);
		ft_free_tab(tmp->in_out);
		free(tmp->in_out_code);
		tmp = tmp->next;
		free(tmp2);
	}
}

void	cmd_free(t_shell *shell)
{
	if (shell->input)
		free(shell->input);
	free_cmd(&shell->command);
}
