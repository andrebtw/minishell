/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_gestion3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:14:41 by anrodri2          #+#    #+#             */
/*   Updated: 2023/07/20 14:26:59 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

extern int	g_code;

int	empty_env_errors(t_shell *shell, size_t *i, int *state, char *env_name)
{
	(void)i;
	if (*state == REDIRECT)
	{
		ft_putstr_fd("⛔️: $", STDERR_FILENO);
		ft_putstr_fd(env_name, STDERR_FILENO);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		return (shell->parsing.error_code_parsing = \
		ERR_ENV_EMPTY_REDIRECT, TRUE);
	}
	return (FALSE);
}

int	error_code_dollar(t_shell *shell, size_t *i, int *state)
{
	char	*error_code;

	if (!(shell->input[*i] == '$' && shell->input[*i + 1] == '?'))
		return (FALSE);
	error_code = ft_itoa(g_code);
	if (!error_code)
		malloc_err_exit(shell);
	if ((*state == DOUBLE_QUOTE || *state == NOT_INIT) || (*state == SPACE_SEP))
	{
		shell->parsing.current_str = ft_strjoin_free(\
		shell->parsing.current_str, error_code, 1, 1);
		if (!shell->parsing.current_str)
			malloc_err_exit(shell);
	}
	if (*state == REDIRECT_DOUBLE_QUOTE || *state == REDIRECT)
	{
		shell->parsing.current_redirect_str = ft_strjoin_free(\
		shell->parsing.current_redirect_str, error_code, 1, 1);
		if (!shell->parsing.current_redirect_str)
			malloc_err_exit(shell);
	}
	*i = *i + 2;
	return (TRUE);
}

int	double_quotes_dollar(t_shell *shell, size_t *i, int *state)
{
	if (shell->input[*i] == '$')
	{
		if (*state == DOUBLE_QUOTE && shell->input[*i + 1] == '\"')
		{
			shell->parsing.current_str = ft_strjoin_free(\
			shell->parsing.current_str, "$", 1, 0);
			if (!shell->parsing.current_str)
				malloc_err_exit(shell);
			*i = *i + 2;
			return (TRUE);
		}
		else if (*state == REDIRECT_DOUBLE_QUOTE
			&& shell->input[*i + 1] == '\"')
		{
			shell->parsing.current_redirect_str = ft_strjoin_free(\
			shell->parsing.current_redirect_str, "$", 1, 0);
			if (!shell->parsing.current_redirect_str)
				malloc_err_exit(shell);
			*i = *i + 2;
			return (TRUE);
		}
	}
	return (FALSE);
}
