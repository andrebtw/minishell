#include "header.h"

void  add_to_end(t_cmd **lst, int type, char **content)
{
    t_cmd *new;

    new = lstcreate(type, (char **)content);
    lstadd_back(lst, new);
}

t_cmd *create_list(t_shell *shell)
{
    t_cmd *lst;

    (void)shell;
    char content1[20][20] = {"ls", "-a"};
    char content2[20][20] = {"|"};
    char content3[20][20] = {"cat", "-e"};
    lst = lstcreate(IS_CMD, (char **)content1);
    add_to_end(&lst, IS_PIPE, (char **)content2);
    add_to_end(&lst, IS_CMD, (char **)content3);
    return (lst);
}

void test(t_shell *shell)
{
    shell->command = create_list(shell);
}
