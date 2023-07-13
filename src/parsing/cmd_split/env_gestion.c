/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_gestion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 06:53:19 by anrodri2          #+#    #+#             */
/*   Updated: 2023/07/11 04:36:40 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

int	quotes_state_redirect(t_shell *shell, size_t i, int state);
int	quotes_state(t_shell *shell, size_t i, int state);
int	heredoc_env_remove(t_shell *shell, size_t *i, int *state);

int	write_dollar(t_shell *shell, size_t *i, int *state)
{
	if (shell->input[*i] == '$' && ft_strchr(" \t\0", shell->input[*i + 1]))
	{
		if (*state >= SPACE_SEP)
		{
			shell->parsing.current_str = ft_strjoin_free_char(\
			shell->parsing.current_str, SEPARATOR, 1);
			if (!shell->parsing.current_str)
				malloc_err_exit(shell);
		}
		if (*state <= REDIRECT)
		{
			shell->parsing.current_redirect_str = ft_strjoin_free_char(\
			shell->parsing.current_redirect_str, SEPARATOR, 1);
			if (!shell->parsing.current_redirect_str)
				malloc_err_exit(shell);
		}
		return (TRUE);
	}
	return (FALSE);
}

int	check_bad_char(t_shell *shell, size_t *i)
{
	if (ft_isdigit(shell->input[*i + 1]) || !(shell->input[*i + 1] == '_'))
	{
		if (!ft_isalpha(shell->input[*i + 1]) || !(shell->input[*i + 1] == '_'))
		{
			if (shell->input[*i] == '$')
				return (FALSE);
			*i = *i + 2;
			return (TRUE);
		}
	}
	return (FALSE);
}

void	put_state(t_shell *shell, size_t *i, int *state)
{
	if (*state >= SPACE_SEP)
		*state = quotes_state(shell, *i, *state);
	else
		*state = quotes_state_redirect(shell, *i, *state);
}

int	skip_special(t_shell *shell, size_t *i, int *state)
{
	if (!(shell->input[*i] == '$'))
		return (TRUE);
	if (*state == SINGLE_QUOTE || *state == REDIRECT_SINGLE_QUOTE)
		return (TRUE);
	if (write_dollar(shell, i, state))
		return (TRUE);
	if (check_bad_char(shell, i))
		return (TRUE);
	return (FALSE);
}

void	env_gestion(t_shell *shell, size_t *i, int *state)
{
	char	*env_name;

	if (heredoc_env_remove(shell, i, state))
		return ;
	if (skip_special(shell, i, state) || error_code_dollar(shell, i, state))
		return ;
	*i = *i + 1;
	env_name = ft_strdup("");
	if (!env_name)
		malloc_err_exit(shell);
	while (shell->input[*i] && 
		(ft_isalnum(shell->input[*i]) || ft_strchr("_", shell->input[*i])))
	{
		env_name = ft_strjoin_free_char(env_name, shell->input[*i], TRUE);
		if (!env_name)
			malloc_err_exit(shell);
		*i = *i + 1;
	}
	if (!(find_env(shell, state, env_name)))
		if (empty_env_errors(shell, i, state, env_name))
			return ;
	split_space_env(shell, i, state);
	if (shell->input[*i] == '$')
		env_gestion(shell, i, state);
	put_state(shell, i, state);
}
