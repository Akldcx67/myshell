#include <stdio.h>
#include <string.h>

#define MAX_CMD 1024

int main()
{
    char cmd[MAX_CMD];

    while (1)
    {
        printf("myshell> ");

        if (fgets(cmd, sizeof(cmd), stdin) == NULL)
        {
            break;
        }


        size_t len = strlen(cmd);
        
        if (len > 0 && cmd[len - 1] == '\n')
            cmd[len - 1] = '\0';

        if (strcmp(cmd, "exit") == 0)
            break;

        printf("Command entered: %s\n", cmd);

        return 0;
    }
}
