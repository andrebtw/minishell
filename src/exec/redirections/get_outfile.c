/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_outfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthibaul <mthibaul@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 12:22:48 by mthibaul          #+#    #+#             */
/*   Updated: 2023/07/13 13:03:22 by mthibaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_code;

void	check_out_redirections(int i, int *outfile, int *append, t_cmd *cmd)
{
	int	tmp;

	tmp = STDOUT_FILENO;
	if (cmd->in_out_code[i] == IS_OUT)
	{
		*outfile = i;
		*append = 0;
		tmp = open(cmd->in_out[i], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	}
	else if (cmd->in_out_code[i] == IS_OUT_APPEND)
	{
		*outfile = i;
		*append = 1;
		tmp = open(cmd->in_out[i], O_CREAT | O_APPEND, 0644);
	}
	if (tmp < 0)
	{
		error_cmd(cmd->content[0], cmd->in_out[*outfile]);
		*outfile = -2;
		return ;
	}
	if (tmp != STDOUT_FILENO && tmp > 0)
		close(tmp);
}
