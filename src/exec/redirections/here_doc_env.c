/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:38:44 by anrodri2          #+#    #+#             */
/*   Updated: 2023/06/27 13:46:39 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*is_in_env(t_shell *shell, t_env **env, char *env_name);

char	*env_exec(t_shell *shell, char *line, size_t *i, char *output_str)
{
	char	*env_name;
	char	*env_value;
	// char	*r_value;

	env_name = ft_strdup("");
	if (!env_name)
		return (malloc_err_exit(shell), NULL);
	*i = *i + 1;
	while (line[*i] && 
			(ft_isalnum(line[*i]) || ft_strchr("_", line[*i])))
	{
		env_name = ft_strjoin_free_char(env_name, line[*i], TRUE);
		if (!env_name)
			return (malloc_err_exit(shell), NULL);
		*i = *i + 1;
	}
	env_value = is_in_env(shell, &shell->env, env_name);
	if (!env_value)
		return (line);
	output_str = ft_strjoin_free(output_str, env_value, 1, 1);
	// r_value = ft_strjoin_free(line, env_value, 1, 1);
	// if (!r_value)
	// 	return (malloc_err_exit(shell), NULL);
	return (output_str);
}

int	check_if_env(char *line, size_t *i)
{
	if (line[*i] != '$')
		return (FALSE);
	if (line[*i] == '$' && line[*i + 1] == '$')
		return (FALSE);
	if (ft_isdigit(line[*i + 1]))
		return (FALSE);
	if (ft_isalpha(line[*i + 1]) || line[*i + 1] == '_')
        return (TRUE);
	return (FALSE);
}

char	*here_doc_env(t_shell *shell, char *line)
{
	size_t	i;
	char	*r_string;

	i = 0;
	r_string = ft_strdup("");
	if (!r_string)
		return (malloc_err_exit(shell), NULL);
	while (line[i])
	{
		if (check_if_env(line, &i))
			r_string = env_exec(shell, line, &i, r_string);
		r_string = ft_strjoin_free_char(r_string, line[i], 1);
		if (!r_string)
			return (malloc_err_exit(shell), NULL);	
		i++;
	}
	return (r_string);
}
