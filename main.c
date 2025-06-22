#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdlib.h>
#include <stdio.h>
#define MAX 1024
#define PATH_MAX 1024
#define MAX_LEN_USER 32
int tokenize_input(char *input, char *argv[], int max_args){
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
        uid_t uid = getuid();

        struct passwd *pw;

        pw = getpwuid(uid);

        char *username = pw->pw_name;
        /*
        uid_t some = getpw(struct passwd *);

        if (some == NULL){
            write(2, "error\n", 5);
        }
        */
        char cd[PATH_MAX];

        getcwd(cd, sizeof(cd));
        
        write(1, username, strlen(username));
        write(1, "[", 1);
        write(1, cd, strlen(cd));
        write(1, "]#: ", 4);
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

        if (strcmp(argv[0], "cd") == 0){

            if (argv[1] == NULL){
                write(2, "cd: missing argument\n", 22);
            }
            else{
                if (chdir(argv[1]) != 0){
                    write(2, "cd: no such directory\n", 23);
                }
            }
            continue;
        }
        pid_t pid = fork();
        
        if (pid == 0){
            if (execvp(argv[0], argv) == -1){
                write(1, "Command not found\n", 19);
                _exit(1);
            }
                execvp(argv[0], argv);
        }
        if (pid > 0){
            wait(NULL);
        }
        if (pid < 0){
            exit(1);
        }

        if (strcmp(argv[0], "exit") == 0){
            break;
        }
    }
    return 0;
}
