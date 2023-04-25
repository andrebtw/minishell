#include "../header.h"

t_cmd   *lstcreate(char **content, char **in_out, char *in_out_code)
{
	t_cmd   *r_value;

	r_value = malloc (sizeof(t_cmd));
	if (!r_value)
		return (NULL);
	r_value->content = content;
	r_value->in_out = in_out;
	r_value->in_out_code = in_out_code;
	r_value->type = IS_CMD;
	r_value->next = NULL;
	return (r_value);
}

t_cmd   *lstinit(void)
{
	t_cmd   *r_value;

	r_value = malloc (sizeof(t_cmd));
	if (!r_value)
		return (NULL);
	r_value->type = IS_CMD;
	r_value->content = NULL;
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
