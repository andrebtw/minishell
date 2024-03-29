/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 16:25:20 by anrodri2          #+#    #+#             */
/*   Updated: 2023/03/16 17:10:03 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *string)
{
	ft_putstr_fd(KRED, 2);
	ft_putstr_fd(string, 2);
	ft_putstr_fd(KNORMAL, 2);
}

void	malloc_err_exit(t_shell *shell)
{
	free(shell->parsing.current_redirect_str);
	free(shell->parsing.current_str);
	free(shell->parsing.current_in_out_code);
	print_error(ERR_MALLOC_MSG);
	exit_clean(ENOMEM, shell);
}
