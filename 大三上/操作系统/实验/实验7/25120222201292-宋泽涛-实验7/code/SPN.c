#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 6  // 最多支持6个进程

// 定义进程结构体
typedef struct {
    char name;           // 进程名
    int arrivalTime;     // 到达时间
    int serviceTime;     // 服务时间
    int remainingTime;   // 剩余时间
    int completionTime;  // 完成时间
    int turnAroundTime;  // 周转时间
    int waitingTime;     // 等待时间
    float responseRatio; // 响应比
} Process;

// 计算周转时间
int calculateTurnAroundTime(int arrivalTime, int completionTime) {
    return completionTime - arrivalTime;
}

// 计算等待时间
int calculateWaitingTime(int turnAroundTime, int serviceTime) {
    return turnAroundTime - serviceTime;
}

// 按服务时间排序
void sortByServiceTime(Process processes[], int numProcesses) {
    for (int i = 0; i < numProcesses - 1; i++) {
        for (int j = i + 1; j < numProcesses; j++) {
            if (processes[i].serviceTime > processes[j].serviceTime) {
                // 交换进程
                Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

// 最短进程优先SPN调度
void scheduleProcesses(Process processes[], int numProcesses) {
    int currentTime = 0;   // 当前时间
    bool isCompleted[MAX_PROCESSES] = {false};  // 用来标记是否已经完成
    int completed = 0;      // 记录已完成进程数量

    // 依照到达时间排序
    sortByServiceTime(processes, numProcesses);

    // SPN 调度
    while (completed < numProcesses) {
        int minServiceTime = 999999;  // 用于找最短的服务时间
        int processIndex = -1;

        // 遍历所有进程，选择服务时间最短的进程
        for (int i = 0; i < numProcesses; i++) {
            // 如果该进程未完成且到达时间小于等于当前时间
            if (!isCompleted[i] && processes[i].arrivalTime <= currentTime) {
                if (processes[i].serviceTime < minServiceTime) {
                    minServiceTime = processes[i].serviceTime;
                    processIndex = i;
                }
            }
        }

        // 如果找到了最短服务时间的进程，则执行
        if (processIndex != -1) {
            currentTime += processes[processIndex].serviceTime;  // 执行进程
            processes[processIndex].completionTime = currentTime; // 设置完成时间
            processes[processIndex].turnAroundTime = calculateTurnAroundTime(processes[processIndex].arrivalTime, processes[processIndex].completionTime);
            processes[processIndex].waitingTime = calculateWaitingTime(processes[processIndex].turnAroundTime, processes[processIndex].serviceTime);
            isCompleted[processIndex] = true;  // 标记该进程已完成
            completed++;  // 更新已完成进程数
        }
    }

    // 输出调度结果
    printf("进程\t到达时间\t服务时间\t完成时间\t周转时间\t等待时间\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("%c\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].name,
               processes[i].arrivalTime,
               processes[i].serviceTime,
               processes[i].completionTime,
               processes[i].turnAroundTime,
               processes[i].waitingTime);
    }
}

int main() {
    // 测试数据1
    Process processes1[MAX_PROCESSES] = {
        {'A', 0, 4, 0, 0, 0, 0},
        {'B', 1, 3, 0, 0, 0, 0},
        {'C', 3, 5, 0, 0, 0, 0},
        {'D', 5, 2, 0, 0, 0, 0},
        {'E', 6, 1, 0, 0, 0, 0}
    };

    printf("测试数据1（最短进程优先SPN调度）：\n");
    scheduleProcesses(processes1, 5);
    printf("\n");

    // 测试数据2
    Process processes2[MAX_PROCESSES] = {
        {'A', 0, 7, 0, 0, 0, 0},
        {'B', 2, 4, 0, 0, 0, 0},
        {'C', 5, 3, 0, 0, 0, 0},
        {'D', 7, 2, 0, 0, 0, 0},
        {'E', 9, 5, 0, 0, 0, 0}
    };

    printf("测试数据2（最短进程优先SPN调度）：\n");
    scheduleProcesses(processes2, 5);
    printf("\n");

    // 测试数据3
    Process processes3[MAX_PROCESSES] = {
        {'A', 0, 2, 0, 0, 0, 0},
        {'B', 1, 5, 0, 0, 0, 0},
        {'C', 3, 3, 0, 0, 0, 0},
        {'D', 4, 4, 0, 0, 0, 0},
        {'E', 6, 6, 0, 0, 0, 0},
        {'F', 8, 2, 0, 0, 0, 0}
    };

    printf("测试数据3（最短进程优先SPN调度）：\n");
    scheduleProcesses(processes3, 6);
    printf("\n");

    // 测试数据4
    Process processes4[MAX_PROCESSES] = {
        {'A', 0, 10, 0, 0, 0, 0},
        {'B', 2, 5, 0, 0, 0, 0},
        {'C', 5, 8, 0, 0, 0, 0},
        {'D', 7, 3, 0, 0, 0, 0},
        {'E', 8, 2, 0, 0, 0, 0}
    };

    printf("测试数据4（最短进程优先SPN调度）：\n");
    scheduleProcesses(processes4, 5);
    printf("\n");

    // 测试数据5
    Process processes5[MAX_PROCESSES] = {
        {'A', 0, 6, 0, 0, 0, 0},
        {'B', 2, 4, 0, 0, 0, 0},
        {'C', 3, 7, 0, 0, 0, 0},
        {'D', 5, 2, 0, 0, 0, 0},
        {'E', 8, 5, 0, 0, 0, 0},
        {'F', 10, 3, 0, 0, 0, 0}
    };

    printf("测试数据5（最短进程优先SPN调度）：\n");
    scheduleProcesses(processes5, 6);
    printf("\n");

    return 0;
}
