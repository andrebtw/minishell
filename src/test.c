#include "header.h"

void test(t_shell *shell)
{
    char content1[20][20] = {"cat", "-e"};
    shell->command = lstcreate(IS_CMD, (char **)content1);

}
