/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:31:03 by anrodri2          #+#    #+#             */
/*   Updated: 2023/03/16 17:12:14 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_code;

void	loop(t_shell *shell)
{
	while (1)
	{
		prompt(shell);
		if (!errors(shell))
		{
			parsing(shell);
			if (!(shell->parsing.error_code_parsing == ERR_ENV_EMPTY_REDIRECT))
			{
				cmd_nb(shell);
				close(shell->fd_stdin);
				close(shell->fd_stdout);
			}
			cmd_free(shell);
		}
		else
			free(shell->input);
	}
}

void	init(char **envp)
{
	t_shell	shell;

	g_code = 0;
	shell.fd_stdin = -1;
	shell.fd_stdout = -1;
	shell.input = NULL;
	if (envp[0])
		shell.env = envp_to_list(envp);
	else
		shell.env = empty_envp(&shell);
	loop(&shell);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	init(envp);
	return (EXIT_SUCCESS);
}
