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

#include "header.h"
#include "../lib/libft.h"

void	loop(t_shell *shell)
{
	while (1)
	{
		prompt(shell);
		parsing(shell);
		// test(shell);
		// debug_print(shell);
	}
}

void	init(void)
{
	t_shell	shell;

	shell.last_err_code = NOT_INIT;
	shell.input = NULL;
	loop(&shell);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	init();
	return (EXIT_SUCCESS);
}
