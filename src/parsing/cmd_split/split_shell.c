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

#include "../../../incl/minishell.h"

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

void	add_to_char(t_shell *shell, size_t *i, int state, char *current_str)
{
	if (state == NOT_INIT)
	{
		if (!ft_strchr(" \t><|", shell->input[*i]))
			current_str = ft_strjoin_free_char(current_str, shell->input[*i], 1);
		else
		{
			
		}
	}
}

void	split_shell(t_shell *shell)
{
	size_t	i;
	int 	state;
	char 	*current_str;

	state = NOT_INIT;
	i = 0;
	current_str = (char *) malloc (sizeof(char *));
	if (!current_str)
		malloc_err_exit(shell);
	while (shell->input[i])
	{
		state = quotes_state(shell, i, state);
		add_to_char(shell, &i, state, current_str);
		i++;
	}
}
