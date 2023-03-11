/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 12:12:41 by anrodri2          #+#    #+#             */
/*   Updated: 2023/03/11 16:58:41 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header.h"

char	*join_code(t_shell *shell, char *r_prompt, char *err_code)
{
	r_prompt = ft_strjoin_free(r_prompt, "\x1B[31m[", 1, 0);
	if (!r_prompt)
		return (free(err_code), malloc_err_exit(shell), NULL);
	r_prompt = ft_strjoin_free(r_prompt, err_code, 1, 1);
	if (!r_prompt)
		return (malloc_err_exit(shell), NULL);
	r_prompt = ft_strjoin_free(r_prompt, "] \x1B[0m", 1, 0);
	if (!r_prompt)
		return (malloc_err_exit(shell), NULL);
	return (r_prompt);
}

char	*create_prompt(t_shell *shell)
{
	char	*r_prompt;
	char	*err_code;

	err_code = ft_itoa(shell->last_err_code);
	if (shell->last_err_code == NOT_INIT)
	{
		r_prompt = ft_strdup(PROMPT);
		if (!r_prompt)
			return (malloc_err_exit(shell), NULL);
		return (r_prompt);
	}
	if (!err_code)
		return (malloc_err_exit(shell), NULL);
	r_prompt = ft_strdup(PROMPT);
	if (!r_prompt)
		return (free(err_code), malloc_err_exit(shell), NULL);
	r_prompt = join_code(shell, r_prompt, err_code);
	return (r_prompt);
}

void	prompt(t_shell *shell)
{
	char	*prompt;

	prompt = create_prompt(shell);
	if (shell->input)
		free(shell->input);
	shell->input = readline(prompt);
	free(prompt);
}
