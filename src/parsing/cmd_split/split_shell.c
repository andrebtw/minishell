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

void	split_shell(t_shell *shell)
{
	size_t	i;

	i = 0;
	shell->tab = (char **) malloc (sizeof(char **));
	if (!shell->tab)
		malloc_err_exit(shell);
	while (shell->input[i])
	{
		while (ft_isspace(shell->input[i]))
			i++;
	}
	return (NULL);
}
