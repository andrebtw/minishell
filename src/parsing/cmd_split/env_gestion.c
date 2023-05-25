/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_gestion.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 06:53:19 by anrodri2          #+#    #+#             */
/*   Updated: 2023/05/18 16:33:32 by anrodri2         ###   ########.fr       */
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

int	write_dollar(t_shell *shell, size_t *i, int *state)
{
	if (shell->input[*i] == '$' && ft_strchr(" \t\0", shell->input[*i + 1]))
	{
		if (*state >= SPACE_SEP)
		{
			shell->parsing.current_str = ft_strjoin_free_char(
				shell->parsing.current_str, SEPARATOR, 1);
			if (!shell->parsing.current_str)
				malloc_err_exit(shell);
		}
		if (*state <= REDIRECT)
		{
			shell->parsing.current_redirect_str = ft_strjoin_free_char(
					shell->parsing.current_redirect_str, SEPARATOR, 1);
			if (!shell->parsing.current_redirect_str)
				malloc_err_exit(shell);
		}
		return (TRUE);
		
	}
	return (FALSE);
}

int	check_bad_char(t_shell *shell, size_t *i, int *state)
{
	(void)state;
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

int	skip_special(t_shell *shell, size_t *i, int *state)
{
	if (!(shell->input[*i] == '$'))
		return (TRUE);
	if (*state == SINGLE_QUOTE || *state == REDIRECT_SINGLE_QUOTE)
		return (TRUE);
	if (write_dollar(shell, i, state))
		return (TRUE);
	if (check_bad_char(shell, i, state))
		return (TRUE);
	return (FALSE);
}

void	env_gestion(t_shell *shell, size_t *i, int *state)
{
	char	*env_name;

	if (skip_special(shell, i, state))
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
	find_env(shell, i, state, env_name);
	split_space_env(shell, i, state);
}
