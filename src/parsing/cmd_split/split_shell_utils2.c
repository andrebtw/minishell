/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 20:05:01 by anrodri2          #+#    #+#             */
/*   Updated: 2023/05/15 06:52:57 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

void	replace_current_tab(t_shell *shell, size_t j, size_t i)
{
	while (shell->parsing.current_tab[i])
	{
		j = 0;
		while (shell->parsing.current_tab[i][j])
		{
			if (shell->parsing.current_tab[i][j] == EMPTY_SPACE)
				shell->parsing.current_tab[i][j] = '\0';
			j++;
		}
		i++;
	}
}

void	replace_current_redirect_tab(t_shell *shell, size_t j, size_t i)
{
	while (shell->parsing.current_redirect_tab[i])
	{
		j = 0;
		while (shell->parsing.current_redirect_tab[i][j])
		{
			if (shell->parsing.current_redirect_tab[i][j] == EMPTY_SPACE)
				shell->parsing.current_redirect_tab[i][j] = '\0';
			j++;
		}
		i++;
	}
}

void	replace_empty_spaces(t_shell *shell)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	replace_current_tab(shell, j, i);
	replace_current_redirect_tab(shell, j, i);
}
