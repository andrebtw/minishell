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

int	state;

void	loop(t_shell *shell, t_env *env)
{
	while (1)
	{
		prompt(shell);
		parsing(shell);
		if (shell->command->content[0])
			check_builtins(shell->command, env);
		//debug_print(shell);
	}
}

void	init(char **envp)
{
	t_shell	shell;
	t_env *env;

	shell.last_err_code = NOT_INIT;
	shell.input = NULL;
	env = envp_to_list(envp);
	loop(&shell, env);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	init(envp);
	return (EXIT_SUCCESS);
}
