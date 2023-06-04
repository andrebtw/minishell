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

int	quotes_state_redirect(t_shell *shell, size_t i, int state);
int	quotes_state(t_shell *shell, size_t i, int state);

int	add_node(t_cmd **cmd, size_t i, t_shell *shell)
{
	t_cmd	*tmp;
	t_cmd	*new;

	(void)i;
	tmp = *cmd;
	if (!tmp->content)
	{
		*cmd = lstcreate(shell->parsing.current_tab, shell->parsing.current_redirect_tab, shell->parsing.current_in_out_code);
		if (!(*cmd))
			return (free(shell->parsing.current_tab), ERR_MALLOC);
		return (EXIT_SUCCESS);
	}
	new = lstcreate(shell->parsing.current_tab, shell->parsing.current_redirect_tab, shell->parsing.current_in_out_code);
	if (!new)
		return (free(shell->parsing.current_tab), ERR_MALLOC);
	lstadd_back(cmd, new);
	return (EXIT_SUCCESS);
}

void	end_found(t_shell *shell, size_t i)
{
	if ((!shell->parsing.current_str[0]) ||
			(shell->parsing.current_str[0] == '\1' &&
			!shell->parsing.current_str[1]))
		add_separator(shell);
	if (shell->parsing.is_empty_env)
	{
		shell->parsing.current_tab = NULL;
		shell->parsing.is_empty_env = FALSE;
	}
	else
	{
		shell->parsing.current_tab = ft_split(shell->parsing.current_str, SEPARATOR);
		if (!shell->parsing.current_tab)
			malloc_err_exit(shell);
	}
	shell->parsing.current_redirect_tab = ft_split(shell->parsing.current_redirect_str, SEPARATOR);
	if (!shell->parsing.current_redirect_tab)
		malloc_err_exit(shell);
	replace_empty_spaces(shell);
	free(shell->parsing.current_str);
	free(shell->parsing.current_redirect_str);
	shell->parsing.current_str = NULL;
	shell->parsing.current_redirect_str = NULL;
	if (add_node(&shell->command, i, shell))
		malloc_err_exit(shell);
}

void	add_to_char(t_shell *shell, size_t *i, int *state)
{
	env_gestion(shell, i, state);
	if (!shell->input[*i])
		return ;
	if (*state == NOT_INIT && !ft_strchr(" \t<>|\'\"", shell->input[*i]))
	{
		shell->parsing.current_str = ft_strjoin_free_char(
				shell->parsing.current_str, shell->input[*i], 1);
		if (ft_strchr("><", shell->input[*i + 1]))
		{
			shell->parsing.current_str = ft_strjoin_free_char(
					shell->parsing.current_str, SEPARATOR, 1);
			if (!shell->parsing.current_str)
				malloc_err_exit(shell);
		}
		return ;
	}
	separators_split(shell, i, state);
	if (*state == SINGLE_QUOTE)
	{
		if (shell->input[*i] != '\'')
			shell->parsing.current_str = ft_strjoin_free_char(
					shell->parsing.current_str, shell->input[*i], 1);
		if (!shell->parsing.current_str)
			malloc_err_exit(shell);
		return ;
	}
	if (*state == DOUBLE_QUOTE)
	{
		if (shell->input[*i] != '\"')
			shell->parsing.current_str = ft_strjoin_free_char(
					shell->parsing.current_str, shell->input[*i], 1);
		if (!shell->parsing.current_str)
			malloc_err_exit(shell);
		return ;
	}
}

void	add_to_char_redirect(t_shell *shell, size_t *i, int *state)
{
	env_gestion(shell, i, state);
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
	int 	state;

	shell->parsing.current_in_out_code = NULL;
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
	while (shell->input[i])
	{
		shell->parsing.is_empty_env = FALSE;
		empty_args(shell, &i, state);
		shell->parsing.quote_end = FALSE;
		if (state > REDIRECT)
		{
			state = quotes_state(shell, i, state);
			add_to_char(shell, &i, &state);
		}
		else
		{
			state = quotes_state_redirect(shell, i, state);
			add_to_char_redirect(shell, &i, &state);
		}
		if (shell->input[i])
			i++;
	}
	end_found(shell, i);
}
