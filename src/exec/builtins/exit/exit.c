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

int	exit_builtin(t_shell *shell, char **args, t_env *env)
{
	printf("exit\n");
	(void)shell;
	(void)args;
	(void)env;
	return (0);
}