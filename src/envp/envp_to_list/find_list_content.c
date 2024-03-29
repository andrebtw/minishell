/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_list_content.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mthibaul <mthibaul@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 12:08:00 by mthibaul          #+#    #+#             */
/*   Updated: 2023/07/13 15:09:39 by mthibaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(char *s, int end);

char	*find_name(char *envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (envp[i] == '=')
			return (ft_strndup(envp, i));
		i++;
	}
	return (ft_strdup(envp));
}

char	*find_value(char *envp)
{
	while (*envp)
	{
		if (*envp == '=')
		{
			envp++;
			if (*envp)
				return (ft_strdup(envp));
			else
				return (NULL);
		}
		envp++;
	}
	return (NULL);
}

char	*ft_strndup(char *s, int end)
{
	char	*return_string;
	int		i;

	return_string = (char *) malloc((end + 1) * sizeof(char));
	if (!return_string)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && i < end)
	{
		return_string[i] = s[i];
		i++;
	}
	return_string[i] = '\0';
	return (return_string);
}
