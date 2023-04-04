#include "../../incl/minishell.h"

t_cmd   *lstcreate(int type, char **content)
{
	t_cmd   *r_value;

	r_value = malloc (sizeof(t_cmd));
	if (!r_value)
		return (NULL);
	r_value->content = content;
	r_value->type = type;
	r_value->next = NULL;
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
