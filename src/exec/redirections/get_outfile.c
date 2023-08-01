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

void	check_out_redirections(int i, int *outfile, int *append, t_shell *shell)
{
	int	tmp;

	tmp = STDOUT_FILENO;
	if (shell->command->in_out_code[i] == IS_OUT)
	{
		*outfile = i;
		*append = 0;
		tmp = open(shell->command->in_out[i], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	}
	else if (shell->command->in_out_code[i] == IS_OUT_APPEND)
	{
		*outfile = i;
		*append = 1;
		tmp = open(shell->command->in_out[i], O_CREAT | O_APPEND, 0644);
	}
	if (tmp < 0)
	{
		error_cmd(shell->command->content[0], shell->command->in_out[*outfile], shell);
		*outfile = -2;
		return ;
	}
	if (tmp != STDOUT_FILENO && tmp > 0)
		close(tmp);
}
