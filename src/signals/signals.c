/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 06:54:35 by anrodri2          #+#    #+#             */
/*   Updated: 2023/06/29 20:34:04 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"
extern int	g_state;

void	ctrl_c(void)
{
	if (g_state == IN_PROMPT)
		g_state = CTRL_C;
	if (g_state == EXECUTION)
		ft_putchar_fd('\n', 1);
	if (g_state == IN_HEREDOC)
	{
		ft_putchar_fd('\n', 1);
		g_state = CTRL_C_HEREDOC;
	}
}

void	ctrl_slash(void)
{
	if (g_state == IN_PROMPT)
		g_state = CTRL_SLASH;
	if (g_state == IN_EXECVE)
		ft_putstr_fd("Quit (core dumped)\n", 2);
}

void	psighandler(int sig, siginfo_t *info, void *ucontext)
{
	(void)info;
	(void)ucontext;
	if (sig == SIGINT)
		ctrl_c();
	if (sig == SIGQUIT)
		ctrl_slash();
}

int	signal_init(t_shell *shell)
{
	struct sigaction	signal;

	(void)shell;
	signal.sa_flags = SA_RESTART | SA_SIGINFO;
	if (sigemptyset(&signal.sa_mask) == -1)
		return (EXIT_FAILURE);
	sigaddset(&signal.sa_mask, SIGINT);
	sigaddset(&signal.sa_mask, SIGQUIT);
	signal.sa_sigaction = psighandler;
	if (sigaction(SIGINT, &signal, NULL) == -1)
		return (EXIT_FAILURE);
	if (sigaction(SIGQUIT, &signal, NULL) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
