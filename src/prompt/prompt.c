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

#include "minishell.h"
extern int	g_state;

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

	if (shell->last_err_code == 0)
	{
		r_prompt = ft_strdup(PROMPT);
		if (!r_prompt)
			return (malloc_err_exit(shell), NULL);
		return (r_prompt);
	}
	err_code = ft_itoa(shell->last_err_code);
	if (!err_code)
		return (malloc_err_exit(shell), NULL);
	r_prompt = ft_strdup(PROMPT);
	if (!r_prompt)
		return (free(err_code), malloc_err_exit(shell), NULL);
	r_prompt = join_code(shell, r_prompt, err_code);
	return (r_prompt);
}

void	empty_prompt(t_shell *shell)
{
	if (g_state == CTRL_SLASH)
		return ;
	if (g_state != CTRL_C)
	{
		ft_putstr_fd("exit\n", 1);
		exit_builtin(shell, NULL, shell->env);
	}
	else
	{
		shell->last_err_code = 130;
		ft_putchar_fd('\n', 1);
		prompt(shell);
	}
}

void	prompt(t_shell *shell)
{
	char	*prompt;

	prompt = create_prompt(shell);
	rl_getc_function = getc;
	g_state = IN_PROMPT;
	signal(SIGQUIT, SIG_IGN);
	shell->input = readline(prompt);
	shell->last_err_code = 0;
	free(prompt);
	if (!shell->input)
		empty_prompt(shell);
	add_history(shell->input);
}
