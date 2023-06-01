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

#include "../incl/minishell.h"
#include "../lib/libft.h"

int	g_state;

void	loop(t_shell *shell)
{
	while (1)
	{
		prompt(shell);
		if (!errors(shell))
		{
			parsing(shell);
			debug_print(shell);
			/* EXEC FUNCTION HERE */
			cmd_free(shell);
		}
		// malloc_err_exit(shell);
	}
}

void	init(char **envp)
{
	t_shell	shell;

	g_state = BEFORE_PROMPT;
	shell.last_err_code = NOT_INIT;
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
