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

int		quotes_state_redirect(t_shell *shell, size_t i, int state);
int		quotes_state(t_shell *shell, size_t i, int state);
void	add_to_char(t_shell *shell, size_t *i, int *state);
void	add_to_char_redirect(t_shell *shell, size_t *i, int *state);
void	split_shell_init(t_shell *shell);
int		add_node(t_cmd **cmd, size_t i, t_shell *shell);
void	end_found(t_shell *shell, size_t i);

void	split_shell(t_shell *shell)
{
	size_t	i;
	int		state;

	split_shell_init(shell);
	state = NOT_INIT;
	i = 0;
	shell->command = lstinit();
	if (!shell->command)
		malloc_err_exit(shell);
	shell->parsing.current_str = ft_strdup("");
	if (!shell->parsing.current_str)
		malloc_err_exit(shell);
	shell->parsing.current_redirect_str = ft_strdup("");
	if (!shell->parsing.current_redirect_str)
	{
		ft_free_char(&shell->parsing.current_str);
		malloc_err_exit(shell);
	}
	split_shell_loop(shell, i, state);
	end_found(shell, i);
	ft_free_char(&shell->parsing.current_in_out_code);
}
