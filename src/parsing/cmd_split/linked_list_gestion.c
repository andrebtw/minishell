/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_gestion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 23:56:02 by anrodri2          #+#    #+#             */
/*   Updated: 2023/08/01 23:57:17 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

int	add_node(t_cmd **cmd, size_t i, t_shell *shell)
{
	t_cmd	*tmp;
	t_cmd	*new;

	(void)i;
	tmp = *cmd;
	if (!tmp->content)
	{
		free(*cmd);
		*cmd = lstcreate(shell->parsing.current_tab, \
		shell->parsing.current_redirect_tab, \
		shell->parsing.current_in_out_code);
		if (!(*cmd))
			return (ft_free_tab(shell->parsing.current_tab), ERR_MALLOC);
		return (EXIT_SUCCESS);
	}
	new = lstcreate(shell->parsing.current_tab, \
	shell->parsing.current_redirect_tab, shell->parsing.current_in_out_code);
	if (!new)
		return (ft_free_tab(shell->parsing.current_tab), ERR_MALLOC);
	lstadd_back(cmd, new);
	return (EXIT_SUCCESS);
}

void	end_found(t_shell *shell, size_t i)
{
	shell->parsing.is_heredoc = FALSE;
	shell->parsing.current_tab = ft_split(\
	shell->parsing.current_str, SEPARATOR);
	if (!shell->parsing.current_tab)
		malloc_err_exit(shell);
	shell->parsing.current_redirect_tab = ft_split(\
	shell->parsing.current_redirect_str, SEPARATOR);
	if (!shell->parsing.current_redirect_tab)
		malloc_err_exit(shell);
	replace_empty_spaces(shell);
	if (add_node(&shell->command, i, shell))
		malloc_err_exit(shell);
	shell->parsing.current_in_out_code = NULL;
	shell->parsing.current_in_out_code = ft_strdup("");
	if (!shell->parsing.current_in_out_code)
		malloc_err_exit(shell);
	ft_free_char(&shell->parsing.current_str);
	ft_free_char(&shell->parsing.current_redirect_str);
}
