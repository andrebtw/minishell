#include "../incl/minishell.h"

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
    char **content1 = malloc(sizeof(char *) * 3);
	content1[0] = "unset";
    content1[1] = "HOME";
    content1[2] = NULL;
	char **content2 = malloc(sizeof(char *) * 2);
	content2[0] = "cd";
    content2[1] = NULL;
	char **content3 = malloc(sizeof(char *) * 2);
	content3[0] = "cat";
	content3[1] = "-e";
    lst = lstcreate(IS_BUILTIN, content1);
    add_to_end(&lst, IS_PIPE, content2);
    add_to_end(&lst, IS_CMD, content3);
    return (lst);
}

void test(t_shell *shell, char **envp)
{
    t_env *env;

    shell->command = create_list(shell);
    env = envp_to_list(envp);
    while (shell->command)
    {
        check_builtins(shell->command, env);
        shell->command = shell->command->next;
    }
}
