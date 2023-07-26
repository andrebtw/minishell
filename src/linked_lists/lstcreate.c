/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstcreate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anrodri2 <anrodri2@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 08:10:55 by anrodri2          #+#    #+#             */
/*   Updated: 2023/07/11 03:53:14 by anrodri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

t_cmd	*lstcreate(char **content, char **in_out, char *in_out_code)
{
	t_cmd	*r_value;

	r_value = malloc (sizeof(t_cmd));
	if (!r_value)
		return (NULL);
	r_value->content = content;
	r_value->in_out = in_out;
	if (in_out_code[0])
	{
		r_value->in_out_code = ft_strdup(in_out_code);
		free(in_out_code);
	}
	else
	{
		free(in_out_code);
		r_value->in_out_code = NULL;
	}
	r_value->type = IS_CMD;
	r_value->next = NULL;
	return (r_value);
}

t_cmd	*lstinit(void)
{
	t_cmd	*r_value;

	r_value = malloc (sizeof(t_cmd));
	if (!r_value)
		return (NULL);
	r_value->type = IS_CMD;
	r_value->content = NULL;
	r_value->next = NULL;
	r_value->in_out = NULL;
	r_value->in_out_code = NULL;
	return (r_value);
}

void	lstadd_back(t_cmd **lst, t_cmd *new)
{
	t_cmd	*tmp;

	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		(*lst) = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}
