/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_shell_utils1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 15:16:41 by anrodri2          #+#    #+#             */
/*   Updated: 2023/04/17 10:32:24 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header.h"

/*
<< heredoc
>> redirect
> redirect
< redirect
*/

void	separators_split(t_shell *shell, size_t *i, int state)
{
	if (state == NOT_INIT && shell->input[*i] == '|')
	{
		end_found(shell, *i, state, IS_CMD);
		shell->parsing.current_str = ft_strjoin_free_char(
				shell->parsing.current_str, shell->input[*i], 1);	
		end_found(shell, *i, state, IS_PIPE);
	}
	else if ((state == NOT_INIT && shell->input[*i] == '<') &&
			(shell->input[*i + 1] == '<'))
	{
		end_found(shell, *i, state, IS_CMD);
		shell->parsing.current_str = ft_strjoin_free_char(
				shell->parsing.current_str, shell->input[*i], 1);
		*i = *i + 1;
		shell->parsing.current_str = ft_strjoin_free_char(
				shell->parsing.current_str, shell->input[*i], 1);	
		end_found(shell, *i, state, IS_HERE_DOC);
	}
	else if ((state == NOT_INIT && shell->input[*i] == '>') &&
			(shell->input[*i + 1] == '>'))
	{
		end_found(shell, *i, state, IS_CMD);
		shell->parsing.current_str = ft_strjoin_free_char(
				shell->parsing.current_str, shell->input[*i], 1);
		*i = *i + 1;
		shell->parsing.current_str = ft_strjoin_free_char(
				shell->parsing.current_str, shell->input[*i], 1);	
		end_found(shell, *i, state, IS_REDIRECT);
	}
	else if (state == NOT_INIT && shell->input[*i] == '>') 
	{
		end_found(shell, *i, state, IS_CMD);
		shell->parsing.current_str = ft_strjoin_free_char(
				shell->parsing.current_str, shell->input[*i], 1);	
		end_found(shell, *i, state, IS_REDIRECT);
	}
	else if (state == NOT_INIT && shell->input[*i] == '<') 
	{
		end_found(shell, *i, state, IS_CMD);
		shell->parsing.current_str = ft_strjoin_free_char(
				shell->parsing.current_str, shell->input[*i], 1);	
		end_found(shell, *i, state, IS_REDIRECT);
	}
}
