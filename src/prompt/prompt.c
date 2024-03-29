/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 12:12:41 by anrodri2          #+#    #+#             */
/*   Updated: 2023/03/11 16:58:41 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_code;

void	empty_prompt(t_shell *shell)
{
	exit_builtin(shell, NULL);
}

void	prompt(t_shell *shell)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, (void *)sig_handler_prompt);
	rl_getc_function = rl_getc;
	shell->input = readline(PROMPT);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (!shell->input)
		empty_prompt(shell);
}
