#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>

// 信号量操作函数
void sem_down(int semid, int sem_num) {
    struct sembuf sem_op = {sem_num, -1, 0}; // P操作：减1
    semop(semid, &sem_op, 1);
}

void sem_up(int semid, int sem_num) {
    struct sembuf sem_op = {sem_num, 1, 0};  // V操作：加1
    semop(semid, &sem_op, 1);
}

int main() {
    int semid; // 信号量集ID
    int pid;   // 进程ID
    key_t key = ftok("semfile_rw", 66); // 创建唯一键值

    // 创建3个信号量: 互斥信号量、写信号量、读者计数信号量
    semid = semget(key, 3, 0666 | IPC_CREAT);
    semctl(semid, 0, SETVAL, 1); // 互斥信号量，初始值为1
    semctl(semid, 1, SETVAL, 1); // 写信号量，初始值为1
    semctl(semid, 2, SETVAL, 0); // 读者计数器信号量，初始值为0

    // 创建子进程
    pid = fork();

    if (pid > 0) { // 父进程-写者
        for (int i = 0; i < 3; i++) {
            sem_down(semid, 1);  // 请求写操作
            printf("写者开始写数据\n");
            sleep(2);  // 模拟写操作时间
            printf("写者结束写数据\n");
            sem_up(semid, 1);  // 释放写锁
            sleep(1);  // 模拟写者的等待时间
        }
        wait(NULL);  // 等待子进程
        semctl(semid, 0, IPC_RMID, 0);  // 删除信号量集
    } else { // 子进程-读者
        for (int i = 0; i < 3; i++) {
            sem_down(semid, 0);  // 互斥访问读者计数器
            if (semctl(semid, 2, GETVAL, 0) == 0) {
                sem_down(semid, 1);  // 如果是第一个读者，阻塞写者
            }
            semctl(semid, 2, SETVAL, semctl(semid, 2, GETVAL, 0) + 1);  // 读者计数+1
            sem_up(semid, 0);  // 释放互斥锁

            printf("读者正在读取数据\n");
            sleep(1);  // 模拟读操作时间

            sem_down(semid, 0);  // 互斥访问读者计数器
            semctl(semid, 2, SETVAL, semctl(semid, 2, GETVAL, 0) - 1);  // 读者计数-1
            if (semctl(semid, 2, GETVAL, 0) == 0) {
                sem_up(semid, 1);  // 如果没有读者了，释放写锁
            }
            sem_up(semid, 0);  // 释放互斥锁

            sleep(1);  // 模拟读者的等待时间
        }
    }
    return 0;
}
