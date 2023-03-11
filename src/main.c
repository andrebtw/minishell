/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:31:03 by anrodri2          #+#    #+#             */
/*   Updated: 2023/03/11 18:35:07 by anrodri2         ###   ########.fr       */
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
	}
}

void	init(void)
{
	t_shell	shell;

	shell.last_err_code = NOT_INIT;
	shell.input = NULL;
	loop(&shell);
}

int	main(void)
{
	init();
	return (EXIT_SUCCESS);
}
