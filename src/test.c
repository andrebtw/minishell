#include "header.h"

// void	add_to_end(t_cmd **lst, int type, char **content)
// {
// 	t_cmd *new;

// 	new = lstcreate(type, (char **)content, NULL, NULL);
// 	lstadd_back(lst, new);
// }

// t_cmd	*create_list(t_shell *shell)
// {
// 	t_cmd	*lst;

// 	(void)shell;
// 	char **content1 = ft_split("ls -a", ' ');
// 	char **content2 = ft_split("|", ' ');
// 	char **content3 = ft_split("cat -e", ' ');
// 	lst = lstcreate(IS_CMD, content1, NULL, NULL);
// 	add_to_end(&lst, IS_PIPE, content2, NULL, NULL);
// 	add_to_end(&lst, IS_CMD, content3, NULL, NULL);
// 	return (lst);
// }

// void	test(t_shell *shell)
// {
// 	shell->command = create_list(shell);
// }
