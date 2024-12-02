#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int main() {
    pid_t pid1, pid2;

    // 创建第一个子进程
    pid1 = fork();

    if (pid1 < 0) {
        // 如果创建失败
        perror("fork failed");
        exit(1);
    } else if (pid1 == 0) {
        // 第一个子进程
        while (1) {
            printf("Child process 1 is running...\n");
            sleep(1);
        }
    } else {
        // 父进程继续创建第二个子进程
        pid2 = fork();
        if (pid2 < 0) {
            // 创建失败
            perror("fork failed");
            exit(1);
        } else if (pid2 == 0) {
            // 子进程2
            while (1) {
                printf("Child process 2 is running...\n");
                sleep(1);
            }
        } else {
            // 父进程
            printf("Parent process is running...\n");
            sleep(5);

            // 杀死第一个子进程
            kill(pid1, SIGTERM);
            printf("Child process 1 was killed by parent process\n");

            // 杀死第二个子进程
            kill(pid2, SIGTERM);
            printf("Child process 2 was killed by parent process\n");

            // 等待两个子进程停止
            wait(NULL);
            wait(NULL);

            printf("Parent process is exiting\n");
        }
    }

    return 0;
}
