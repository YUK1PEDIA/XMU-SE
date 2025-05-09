#include <stdio.h>

#define MAX_PROCESSES 6 // 最多支持6个进程

// 定义进程结构体
typedef struct {
    char name;       // 进程名
    int arrivalTime; // 到达时间
    int serviceTime; // 服务时间
    int completionTime; // 完成时间
    int turnAroundTime; // 周转时间
    int waitingTime;    // 等待时间
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

// 计算响应比
float calculateResponseRatio(int waitingTime, int serviceTime) {
    return (float)(waitingTime + serviceTime) / serviceTime;
}

// 调度函数
void scheduleProcesses(Process processes[], int numProcesses) {
    int currentTime = 0; // 当前时间，初始时为 0
    int i;

    // FCFS调度
    for (i = 0; i < numProcesses; i++) {
        // 进程到达时间早于当前时间时，更新当前时间
        if (currentTime < processes[i].arrivalTime) {
            currentTime = processes[i].arrivalTime;
        }

        // 计算完成时间
        processes[i].completionTime = currentTime + processes[i].serviceTime;

        // 计算周转时间
        processes[i].turnAroundTime = calculateTurnAroundTime(processes[i].arrivalTime, processes[i].completionTime);

        // 计算等待时间
        processes[i].waitingTime = calculateWaitingTime(processes[i].turnAroundTime, processes[i].serviceTime);

        // 计算响应比
        processes[i].responseRatio = calculateResponseRatio(processes[i].waitingTime, processes[i].serviceTime);

        // 更新当前时间
        currentTime = processes[i].completionTime;
    }

    // 输出调度结果
    printf("进程\t到达时间\t服务时间\t完成时间\t周转时间\t等待时间\t响应比\n");
    for (i = 0; i < numProcesses; i++) {
        printf("%c\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%.2f\n",
               processes[i].name,
               processes[i].arrivalTime,
               processes[i].serviceTime,
               processes[i].completionTime,
               processes[i].turnAroundTime,
               processes[i].waitingTime,
               processes[i].responseRatio);
    }
}

int main() {
    // 测试数据1
    Process processes1[MAX_PROCESSES] = {
        {'A', 0, 4, 0, 0, 0, 0.0},
        {'B', 1, 3, 0, 0, 0, 0.0},
        {'C', 3, 5, 0, 0, 0, 0.0},
        {'D', 5, 2, 0, 0, 0, 0.0},
        {'E', 6, 1, 0, 0, 0, 0.0}
    };
    
    printf("测试数据1：\n");
    scheduleProcesses(processes1, 5);
    printf("\n");

    // 测试数据2
    Process processes2[MAX_PROCESSES] = {
        {'A', 0, 7, 0, 0, 0, 0.0},
        {'B', 2, 4, 0, 0, 0, 0.0},
        {'C', 5, 3, 0, 0, 0, 0.0},
        {'D', 7, 2, 0, 0, 0, 0.0},
        {'E', 9, 5, 0, 0, 0, 0.0}
    };
    
    printf("测试数据2：\n");
    scheduleProcesses(processes2, 5);
    printf("\n");

    // 测试数据3
    Process processes3[MAX_PROCESSES] = {
        {'A', 0, 2, 0, 0, 0, 0.0},
        {'B', 1, 5, 0, 0, 0, 0.0},
        {'C', 3, 3, 0, 0, 0, 0.0},
        {'D', 4, 4, 0, 0, 0, 0.0},
        {'E', 6, 6, 0, 0, 0, 0.0},
        {'F', 8, 2, 0, 0, 0, 0.0}
    };

    printf("测试数据3：\n");
    scheduleProcesses(processes3, 6);
    printf("\n");

    // 测试数据4
    Process processes4[MAX_PROCESSES] = {
        {'A', 0, 10, 0, 0, 0, 0.0},
        {'B', 2, 5, 0, 0, 0, 0.0},
        {'C', 5, 8, 0, 0, 0, 0.0},
        {'D', 7, 3, 0, 0, 0, 0.0},
        {'E', 8, 2, 0, 0, 0, 0.0}
    };

    printf("测试数据4：\n");
    scheduleProcesses(processes4, 5);
    printf("\n");

    // 测试数据5
    Process processes5[MAX_PROCESSES] = {
        {'A', 0, 6, 0, 0, 0, 0.0},
        {'B', 2, 4, 0, 0, 0, 0.0},
        {'C', 3, 7, 0, 0, 0, 0.0},
        {'D', 5, 2, 0, 0, 0, 0.0},
        {'E', 8, 5, 0, 0, 0, 0.0},
        {'F', 10, 3, 0, 0, 0, 0.0}
    };

    printf("测试数据5：\n");
    scheduleProcesses(processes5, 6);
    printf("\n");

    return 0;
}
