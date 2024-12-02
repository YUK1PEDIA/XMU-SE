#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>

// 定义信号量操作的结构体
struct sembuf sem_op;

// 初始化信号量操作函数
void sem_down(int semid, int sem_num) {
    sem_op.sem_num = sem_num;  // 指定信号量编号
    sem_op.sem_op = -1;        // P操作：减1
    sem_op.sem_flg = 0;
    semop(semid, &sem_op, 1);
}

void sem_up(int semid, int sem_num) {
    sem_op.sem_num = sem_num;  // 指定信号量编号
    sem_op.sem_op = 1;         // V操作：加1
    sem_op.sem_flg = 0;
    semop(semid, &sem_op, 1);
}

int main() {
    int semid; // 信号量集ID
    int pid;   // 进程ID
    int buffer = 0;  // 缓冲区
    key_t key = ftok("semfile", 65); // 创建唯一键值

    // 创建3个信号量: 空位信号量、满位信号量、互斥信号量
    semid = semget(key, 3, 0666 | IPC_CREAT);
    semctl(semid, 0, SETVAL, 1); // 互斥信号量，初始值为1
    semctl(semid, 1, SETVAL, 0); // 满位信号量，初始值为0
    semctl(semid, 2, SETVAL, 5); // 空位信号量，初始值为5

    // 创建子进程
    pid = fork();

    if (pid > 0) { // 父进程-生产者
        for (int i = 0; i < 5; i++) {
            sem_down(semid, 2);  // 等待空位
            sem_down(semid, 0);  // 互斥访问缓冲区

            buffer++;  // 生产产品
            printf("生产者生产了产品 %d\n", buffer);

            sem_up(semid, 0);  // 释放互斥锁
            sem_up(semid, 1);  // 增加满位

            sleep(1);  // 模拟生产时间
        }
        wait(NULL);  // 等待子进程
        semctl(semid, 0, IPC_RMID, 0);  // 删除信号量集
    } else { // 子进程-消费者
        for (int i = 0; i < 5; i++) {
            sem_down(semid, 1);  // 等待满位
            sem_down(semid, 0);  // 互斥访问缓冲区

            printf("消费者消费了产品 %d\n", buffer);
            buffer--;  // 消费产品

            sem_up(semid, 0);  // 释放互斥锁
            sem_up(semid, 2);  // 增加空位

            sleep(2);  // 模拟消费时间
        }
    }
    return 0;
}
