#include <string.h>
#include <unistd.h>

int main()
{
    char str[64];

    while(1)
    {
        write(1, "#: ", 3);

        ssize_t str_size = read(0, str, sizeof(str));

        if (str_size == 0){
            write(1, "\n", 1);
            break;
        }

        str[str_size] = '\0'; 
        
        if (str_size > 0 && str[str_size - 1] == '\n'){
            str[str_size - 1] = '\0';
        }

        if (strcmp(str, "exit") == 0){
            break;
        }

        write(1, str, strlen(str));
        write(1, "\n", 1);
    }
    return 0;
}
