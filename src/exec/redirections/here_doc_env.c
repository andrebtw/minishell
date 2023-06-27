/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:38:44 by anrodri2          #+#    #+#             */
/*   Updated: 2023/06/26 15:28:07 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	check_if_env(char *line, size_t *i)
// {
// 	if (line[*i] != '$')
// 		return (FALSE);
// 	if (line[*i] == '$' && line[*i + 1] == '$')
// 		return (FALSE);
// 	if (ft_isalpha(line[*i + 1]))
// 		return (FALSE);
// 	if ()
// 	return (TRUE);
// }

// char	*here_doc_env(char *line)
// {
// 	size_t	i;
// 	char	*r_string;

// 	r_string = ft_strdup("");
// 	if (!r_string)
// 		return (NULL);
// 	while (line[i])
// 	{
// 		if (check_if_env(line, &i))

// 		r_string = ft_strjoin_free_char(r_string, line[i], 1);
// 		if (!r_string)
// 			return (NULL);	
// 		i++;
// 	}
// 	return (r_string);
// }
