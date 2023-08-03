/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_with_plus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthibaul <mthibaul@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 18:21:00 by mthibaul          #+#    #+#             */
/*   Updated: 2023/08/03 18:21:00 by mthibaul         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	already_exists(char *name, char *value, t_env *env, t_shell *shell);
char		*name_without_plus(char *arg);
int			add_to_var(char *arg, t_env *env, t_shell *shell);

int	check_plus(char *arg, t_env *env, t_shell *shell)
{
	int	i;

	printf("HERE\n");
	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '=' && arg[i - 1] == '+')
		{
			if (already_exists(name_without_plus(arg), NULL, env, shell) == FALSE)
				return (envadd_elem(env, name_without_plus(arg), \
					find_value(arg), TRUE));
			else
				return (add_to_var(arg, env, shell));
		}
	}
	return (-1);
}

char	*name_without_plus(char *arg)
{
	char *name;
	int	i;

	i = -1;
	name = find_name(arg);
	while (name[++i])
	{
		if (name[i] == '+')
			name[i] = '\0';
	}
	return (name);
}

int	add_to_var(char *arg, t_env *env, t_shell *shell)
{
	char	*name;
	char	*value;

	name = name_without_plus(arg);
	value = find_value(arg);
	while (ft_strcmp(env->name, name) != 0)
		env = env->next;
	free(name);
	if (env->value && value)
	{
		env->value = ft_strjoin_free(env->value, value, 1, 1);
		if (!env->value)
			malloc_err_exit(shell);
	}
	else if (value)
		env->value = value;
	return (0);
}

