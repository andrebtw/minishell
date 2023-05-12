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

#define DOUBLE_QUOTE -15
#define SINGLE_QUOTE -16
#define SPACE_SEP -17
#define REDIRECT -18
#define REDIRECT_SINGLE_QUOTE -19
#define REDIRECT_DOUBLE_QUOTE -20
#define REDIRECT_END -21

int 	quotes_state_redirect(t_shell *shell, size_t i, int state)
{
	if (state == REDIRECT && ft_strchr(" \t<>|", shell->input[i]))
	{
		shell->parsing.current_redirect_str = ft_strjoin_free_char(
				shell->parsing.current_redirect_str, SEPARATOR, 1);
		if (!shell->parsing.current_redirect_str)
			malloc_err_exit(shell);
		return (NOT_INIT);
	}
	if (shell->input[i] == '\'' && state == REDIRECT)
		return (REDIRECT_SINGLE_QUOTE);
	if (shell->input[i] == '\"' && state == REDIRECT)
		return (REDIRECT_DOUBLE_QUOTE);
	if (shell->input[i] == '\'' && state == REDIRECT_SINGLE_QUOTE)
		return (shell->parsing.quote_end = TRUE, REDIRECT);
	if (shell->input[i] == '\"' && state == REDIRECT_DOUBLE_QUOTE)
		return (shell->parsing.quote_end = TRUE, REDIRECT);
	if (state == REDIRECT_DOUBLE_QUOTE || state == REDIRECT_SINGLE_QUOTE)
		return (state);
	return (REDIRECT);
}

int 	quotes_state(t_shell *shell, size_t i, int state)
{
	if (state == SPACE_SEP && ft_strchr(" \t", shell->input[i]))
		return (SPACE_SEP);
	if (state == NOT_INIT && ft_strchr(" \t", shell->input[i]))
	{
		shell->parsing.current_str = ft_strjoin_free_char(
				shell->parsing.current_str, SEPARATOR, 1);
		if (!shell->parsing.current_str)
			malloc_err_exit(shell);
		return (SPACE_SEP);
	}
	if (shell->input[i] == '\'' && state == SINGLE_QUOTE)
		return (shell->parsing.quote_end = TRUE, NOT_INIT);
	if ((shell->input[i] == '\'' && state == NOT_INIT) ||
			(shell->input[i] == '\'' && state == SPACE_SEP))
		return (SINGLE_QUOTE);
	if (shell->input[i] == '\"' && state == DOUBLE_QUOTE)
		return (shell->parsing.quote_end = TRUE, NOT_INIT);
	if ((shell->input[i] == '\"' && state == NOT_INIT) || 
			(shell->input[i] == '\"' && state == SPACE_SEP))
		return (DOUBLE_QUOTE);
	if (state == DOUBLE_QUOTE || state == SINGLE_QUOTE)
		return (state);
	return (NOT_INIT);
}

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

void	end_found(t_shell *shell, size_t i, int state)
{
	char	**content;

	(void)i;
	(void)state;
	(void)content;
	add_separator(shell);
	shell->parsing.current_tab = ft_split(shell->parsing.current_str, SEPARATOR);
	shell->parsing.current_redirect_tab = ft_split(shell->parsing.current_redirect_str, SEPARATOR);
	replace_empty_spaces(shell);
	free(shell->parsing.current_str);
	free(shell->parsing.current_redirect_str);
	shell->parsing.current_str = NULL;
	shell->parsing.current_redirect_str = NULL;
	if (!shell->parsing.current_tab)
		malloc_err_exit(shell);
	if (add_node(&shell->command, i, shell))
		malloc_err_exit(shell);
}

void	add_to_char(t_shell *shell, size_t *i, int *state)
{
	if (*state == NOT_INIT && !ft_strchr(" \t<>|$\'\"", shell->input[*i]))
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
	if (*state == REDIRECT && !ft_strchr("<>|$\'\"", shell->input[*i]))
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
	end_found(shell, i, state);
}
