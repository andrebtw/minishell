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
			return (free(shell->parsing.current_tab), ERR_MALLOC);
		return (EXIT_SUCCESS);
	}
	new = lstcreate(shell->parsing.current_tab, \
	shell->parsing.current_redirect_tab, shell->parsing.current_in_out_code);
	if (!new)
		return (free(shell->parsing.current_tab), ERR_MALLOC);
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
	free(shell->parsing.current_str);
	free(shell->parsing.current_redirect_str);
	shell->parsing.current_str = NULL;
	shell->parsing.current_redirect_str = NULL;
}

void	add_to_char_redirect(t_shell *shell, size_t *i, int *state)
{
	env_gestion(shell, i, state);
	if (!shell->input[*i])
		return ;
	if (*state == REDIRECT && !ft_strchr("<>|\'\"", shell->input[*i]))
	{
		shell->parsing.current_redirect_str = ft_strjoin_free_char(
				shell->parsing.current_redirect_str, shell->input[*i], 1);
		return ;
	}
	separators_split(shell, i, state);
	if (*state == REDIRECT_SINGLE_QUOTE)
	{
		if (shell->input[*i] != '\'')
			shell->parsing.current_redirect_str = ft_strjoin_free_char(
					shell->parsing.current_redirect_str, shell->input[*i], 1);
		return ;
	}
	if (*state == REDIRECT_DOUBLE_QUOTE)
	{
		if (shell->input[*i] != '\"')
			shell->parsing.current_redirect_str = ft_strjoin_free_char(
					shell->parsing.current_redirect_str, shell->input[*i], 1);
		return ;
	}
}

void	split_shell(t_shell *shell)
{
	size_t	i;
	int		state;

	shell->parsing.is_heredoc = FALSE;
	shell->parsing.current_in_out_code = NULL;
	shell->parsing.error_code_parsing = FALSE;
	state = NOT_INIT;
	shell->parsing.quote_end = FALSE;
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
		free(shell->parsing.current_str);
		malloc_err_exit(shell);
	}
	split_shell_loop(shell, i, state);
	end_found(shell, i);
	free(shell->parsing.current_in_out_code);
}
