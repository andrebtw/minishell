/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:03:17 by anrodri2          #+#    #+#             */
/*   Updated: 2023/03/17 22:48:30 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

int	same_word(char *cmd, char *string)
{
	int	i;

	i = 0;
	if (!cmd)
		return (FALSE);
	if (!cmd[i])
		return (FALSE);
	while (cmd[i])
	{
		if (cmd[i] != string[i])
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	is_builtin_check(char *cmd_to_check)
{
	if (same_word(cmd_to_check, "echo"))
		return (TRUE);
	if (same_word(cmd_to_check, "cd"))
		return (TRUE);
	if (same_word(cmd_to_check, "pwd"))
		return (TRUE);
	if (same_word(cmd_to_check, "export"))
		return (TRUE);
	if (same_word(cmd_to_check, "unset"))
		return (TRUE);
	if (same_word(cmd_to_check, "env"))
		return (TRUE);
	if (same_word(cmd_to_check, "exit"))
		return (TRUE);
	return (FALSE);
}

void	check_cmds(t_cmd **cmd)
{
	t_cmd	*tmp;

	tmp = *cmd;
	if (!tmp->content)
		return ;
	while (tmp->next)
	{
		if (is_builtin_check(tmp->content[0]))
			tmp->type = IS_BUILTIN;
		tmp = tmp->next;
	}
	if (is_builtin_check(tmp->content[0]))
		tmp->type = IS_BUILTIN;
}

void	detect_builtin(t_shell *shell)
{
	check_cmds(&shell->command);
}

void	parsing(t_shell *shell)
{
	split_shell(shell);
	if (shell->parsing.error_code_parsing_saved == ERR_ENV_EMPTY_LINE)
	{
		if (!shell->command->content && !shell->command->next)
			shell->parsing.error_code_parsing_saved = ERR_ENV_EMPTY_FULL;
	}
	if (!(shell->parsing.error_code_parsing_saved <= ERR_ENV_EMPTY_REDIRECT))
		detect_builtin(shell);
}
