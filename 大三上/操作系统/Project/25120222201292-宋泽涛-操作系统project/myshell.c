#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024

// 执行用户输入的命令
void execute_command(char *command) {
    char *args[MAX_COMMAND_LENGTH / 2 + 1];
    int i = 0;

    args[i] = strtok(command, " ");
    while (args[i] != NULL) {
        i++;
        args[i] = strtok(NULL, " ");
    }

    if (i == 0) return;

    // 如果输入命令是 "exit"，退出 shell
    if (strcmp(args[0], "exit") == 0) {
        exit(0);
    }

    // 如果输入命令是 "mycommand"，运行 ./mycommand
    if (strcmp(args[0], "mycommand") == 0) {
        // 调用已经编译好的 mycommand
        if (fork() == 0) {
            // 子进程执行 mycommand
            execl("./mycommand", "./mycommand", (char *)NULL);
            perror("Execution failed");
            exit(1);
        } else {
            // 父进程等待子进程完成
            wait(NULL);
        }
        return;
    }

    // 处理其他普通命令
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // 子进程执行命令
        if (execvp(args[0], args) == -1) {
            perror("Execution failed");
        }
        exit(1);
    } else {
        // 父进程等待子进程完成
        wait(NULL);
    }
}

int main() {
    char command[MAX_COMMAND_LENGTH];

    while (1) {
        printf("myshell> ");
        if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL) {
            break;
        }

        // 去掉末尾的换行符
        command[strcspn(command, "\n")] = '\0';
        execute_command(command);
    }

    return 0;
}
