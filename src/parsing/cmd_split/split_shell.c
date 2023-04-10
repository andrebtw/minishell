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
#define SPACE_SEP -17

int 	quotes_state(t_shell *shell, size_t i, int state)
{
	if (state == SPACE_SEP && ft_strchr(" \t", shell->input[i]))
		return (SPACE_SEP);
	if (state == NOT_INIT && ft_strchr(" \t", shell->input[i]))
	{
		shell->parsing.current_str = ft_strjoin_free_char(
				shell->parsing.current_str, ' ', 1);
		if (!shell->parsing.current_str)
			malloc_err_exit(shell);
		return (SPACE_SEP);
	}
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

t_cmd	*end_found(t_shell *shell, size_t i, int state)
{
	t_cmd	*lst;
	char	**content;

	(void)i;
	(void)state;
	content = ft_split(shell->parsing.current_str, ' ');
	free(shell->parsing.current_str);
	shell->parsing.current_str = NULL;
	if (!content)
		malloc_err_exit(shell);
	lst = lstcreate(IS_CMD, content);
	if (!lst)
	{
		free(content);
		malloc_err_exit(shell);
	}
	return (lst);
}

void	add_to_char(t_shell *shell, size_t i, int state)
{
	if (state == NOT_INIT && !ft_strchr(" \t<>|$\'\"", shell->input[i]))
		shell->parsing.current_str = ft_strjoin_free_char(shell->parsing.current_str, shell->input[i], 1);
	if (state == NOT_INIT && shell->input[i] == '|')
	{
		shell->command = end_found(shell, i, state);
	}
}

void	split_shell(t_shell *shell)
{
	size_t	i;
	int 	state;

	state = NOT_INIT;
	i = 0;
	shell->parsing.current_str = ft_strdup("");
	if (!shell->parsing.current_str)
		malloc_err_exit(shell);
	while (shell->input[i])
	{
		state = quotes_state(shell, i, state);
		add_to_char(shell, i, state);
		i++;
	}
	// ft_printf("%s", shell->parsing.current_str);
}
