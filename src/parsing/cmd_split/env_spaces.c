/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_spaces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:42:08 by anrodri2          #+#    #+#             */
/*   Updated: 2023/05/29 15:07:55 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../incl/minishell.h"

char	*env_spaces_loop(char **tab, size_t i)
{
	char	*r_value;

	r_value = ft_strdup("");
	if (!r_value)
		return (NULL);
	while (tab[i])
	{
		r_value = ft_strjoin_free(r_value, tab[i], 1, 0);
		if (!r_value)
			return (NULL);
		if (tab[i + 1])
		{
			r_value = ft_strjoin_free_char(r_value, SEPARATOR, 1);
			if (!r_value)
				return (NULL);
		}
		i++;
	}
	return (r_value);
}

char	*env_spaces(char *env)
{
	char	*r_value;
	char	**tab;
	size_t	i;

	tab = ft_split(env, ' ');
	if (!tab)
		return (free(env), env = NULL, NULL);
	free(env);
	i = 0;
	r_value = env_spaces_loop(tab, i);
	if (!r_value)
		return (ft_free_tab(tab), NULL);
	ft_free_tab(tab);
	return (r_value);
}
