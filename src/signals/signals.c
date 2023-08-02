/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 06:54:35 by anrodri2          #+#    #+#             */
/*   Updated: 2023/08/02 22:35:24 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

extern int	g_code;

void	sig_handler_prompt(const int signal)
{
	if (signal == SIGINT)
	{
		g_code = 130;
		rl_on_new_line();
		rl_replace_line("\0", 1);
		write(1, "\n", 1);
		rl_redisplay();
	}
}

void	sig_handler_cmd(const int signal)
{
	if (signal == SIGINT)
	{
		g_code = 130;
		write(1, "\n", 1);
	}
	if (signal == SIGQUIT)
	{
		g_code = 131;
		ft_putstr_fd("Quit\n", 1);
	}
}

void	sig_check_cmd_signal(int status, t_shell *shell)
{
	reset_fd(shell);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			g_code = 130;
			ft_printf("\n");
		}
		if (WTERMSIG(status) == SIGQUIT)
		{
			g_code = 131;
			ft_printf("Quit\n");
		}
	}
}

void	sig_handler_heredoc(const int signal)
{
	if (signal == SIGINT)
	{
		g_code = 130;
		write(1, "\n", 1);
	}
}
