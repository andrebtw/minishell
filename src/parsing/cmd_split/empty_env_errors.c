/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_env_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:14:41 by anrodri2          #+#    #+#             */
/*   Updated: 2023/06/06 19:52:32 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

int	empty_env_errors(t_shell *shell, size_t *i, int *state, char *env_name)
{
	if (*state == NOT_INIT)
	{
		if (!shell->input[*i] || ft_strchr(" \t<>|", shell->input[*i]))
		{
			if (!shell->parsing.current_str || !shell->parsing.current_str[0])
				return (shell->parsing.error_code_parsing = ERR_ENV_EMPTY_LINE, TRUE);
		}
	}
	if (*state == REDIRECT)
	{
		ft_putstr_fd("⛔️: $", STDERR_FILENO);
		ft_putstr_fd(env_name, STDERR_FILENO);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		return (shell->parsing.error_code_parsing = ERR_ENV_EMPTY_REDIRECT, TRUE);
	}
	return (FALSE);
}
