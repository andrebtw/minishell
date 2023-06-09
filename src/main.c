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

int	g_state;

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
				debug_print(shell);
				cmd_nb(shell);
				wait(NULL);
			}
			cmd_free(shell);
		}
	}
}

void	init(char **envp)
{
	t_shell	shell;

	g_state = BEFORE_PROMPT;
	shell.last_err_code = 0;
	shell.input = NULL;
	shell.env = envp_to_list(envp);
	signal_init(&shell);
	loop(&shell);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	init(envp);
	return (EXIT_SUCCESS);
}
