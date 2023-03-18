/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 00:36:50 by anrodri2          #+#    #+#             */
/*   Updated: 2023/03/17 23:10:38 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"
#define DOUBLE_QUOTE -15
#define SINGLE_QUOTE -16

int 	quotes_state(t_shell *shell, size_t i, int state)
{
	if (shell->input[i] == '\'' && state == SINGLE_QUOTE)
		return (NOT_INIT);
	if (shell->input[i] == '\'' && state == NOT_INIT)
		return (SINGLE_QUOTE);
	if (shell->input[i] == '\"' && state == DOUBLE_QUOTE)
		return (NOT_INIT);
	if (shell->input[i] == '\"' && state == NOT_INIT)
		return (DOUBLE_QUOTE);
	return (NOT_INIT);
}

void	split_shell(t_shell *shell)
{
	size_t	i;
	int 	state;
	char 	*current_str;

	state = NOT_INIT;
	i = 0;
	shell->tab = (char **) malloc (sizeof(char **));
	if (!shell->tab)
		malloc_err_exit(shell);
	while (shell->input[i])
	{
		state = quotes_state(shell, i, state);

		i++;
	}
}
