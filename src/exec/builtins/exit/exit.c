/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 17:39:17 by anrodri2          #+#    #+#             */
/*   Updated: 2023/03/11 17:41:43 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_num(char *str);

int	exit_builtin(t_shell *shell, char **args)
{
	long long	return_value;

	errno = 0;
	return_value = 0;
	ft_printf("exit\n");
	if (args && args[1])
	{
		if (args[2])
			return (ft_putstr_fd("exit: too many arguments\n" \
				, STDERR_FILENO), 1);
		return_value = ft_atoll(args[1]);
		if (!is_num(args[1]) || errno)
		{
			print_builtin_error("exit", args[1]);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			exit_clean(2, shell);
		}
	}
	exit_clean(return_value, shell);
	return (0);
}

void	exit_clean(long long return_value, t_shell *shell)
{
	if (shell->fd_stdout >= 0 && shell->fd_stdin >= 0)
	{
		close(shell->fd_stdout);
		close(shell->fd_stdin);
	}
	if (shell->env->name != NULL)
		free_env(shell->env);
	if (shell && shell->input)
		cmd_free(shell);
	rl_clear_history();
	exit((unsigned char) return_value);
}

int	is_num(char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (FALSE);
		str++;
	}
	return (TRUE);
}
