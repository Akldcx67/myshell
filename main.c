#include <string.h>
#include <unistd.h>
#define MAX 64

int tokenize_input(char *input, char *argv[], int max_args)
{
    char *p = input;
    int i = 0;

    while(*p != '\0'){
        while(*p == ' ') p++;

        if (*p == '\0'){
            break;
        }
        else{
            argv[i] = p;

            if (i >= max_args - 1){
                break;
            }

            while (*p != ' ' && *p != '\0'){ 
                p++;
            }
            if (*p == ' '){
                    *p = '\0';
                    p++;
             }
            }
        i++;
        }

    argv[i] = NULL;

    return i;
}
int main(){
    char str[MAX];

    while(1){
        write(1, "#: ", 3);
        ssize_t str_size = read(0, str, sizeof(str));

        if (str_size == 0){
            write(1, "\n", 1);
            break;
        }
        if (str_size > 0 && str[str_size - 1] == '\n'){
            str[str_size - 1] = '\0';
        }

        char *argv[MAX];
        int argc = tokenize_input(str, argv, MAX);

        if (argc == 0) continue;

        if (strcmp(argv[0], "exit") == 0){
            break;
        }
        write(1, argv[0], strlen(argv[0]));
        write(1, "\n", 1);
    }
    return 0;
}
