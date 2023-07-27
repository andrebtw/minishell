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

#include "minishell.h"

extern int	g_code;

void	free_cmd_pipe(t_cmd *cmd, pid_t pid)
{
	int	ret_value;

	ret_value = 0;
	if (cmd->in_out_code)
		waitpid(pid, &ret_value, 0);
	if (!cmd->next && ret_value != 0)
		g_code = 1;
	ft_free_tab(cmd->content);
	ft_free_tab(cmd->in_out);
	free(cmd->in_out_code);
}

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
