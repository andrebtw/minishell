/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_env_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:14:41 by anrodri2          #+#    #+#             */
/*   Updated: 2023/06/04 16:41:28 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

int	empty_env_errors(t_shell *shell, size_t *i, int *state)
{
	if (*state == NOT_INIT)
	{
		if (!shell->input[*i] || ft_strchr(" \t<>|", shell->input[*i]))
			return (shell->parsing.is_empty_env = TRUE, TRUE);
	}
	return (FALSE);
}
