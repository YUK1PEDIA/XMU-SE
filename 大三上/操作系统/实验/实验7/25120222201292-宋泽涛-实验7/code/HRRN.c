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

// 计算响应比
float calculateResponseRatio(int waitingTime, int serviceTime) {
    return (float)(waitingTime + serviceTime) / serviceTime;
}

// 最高响应比优先HRRN调度
void scheduleProcesses(Process processes[], int numProcesses) {
    int currentTime = 0;   // 当前时间
    bool isCompleted[MAX_PROCESSES] = {false};  // 用来标记是否已经完成
    int completed = 0;      // 记录已完成进程数量

    // 初始化剩余服务时间
    for (int i = 0; i < numProcesses; i++) {
        processes[i].remainingTime = processes[i].serviceTime;
    }

    // HRRN调度
    while (completed < numProcesses) {
        int highestResponseRatioIndex = -1;
        float highestResponseRatio = -1;

        // 遍历所有进程，选择响应比最高的进程
        for (int i = 0; i < numProcesses; i++) {
            // 如果该进程未完成且到达时间小于等于当前时间
            if (!isCompleted[i] && processes[i].arrivalTime <= currentTime) {
                // 计算当前进程的响应比
                int waitingTime = currentTime - processes[i].arrivalTime;
                float responseRatio = calculateResponseRatio(waitingTime, processes[i].serviceTime);

                // 更新响应比最高的进程
                if (responseRatio > highestResponseRatio) {
                    highestResponseRatio = responseRatio;
                    highestResponseRatioIndex = i;
                }
            }
        }

        // 如果找到了响应比最高的进程，则执行
        if (highestResponseRatioIndex != -1) {
            // 执行进程1单位时间
            currentTime++;
            processes[highestResponseRatioIndex].remainingTime--;

            // 如果进程执行完毕，更新完成时间和周转时间
            if (processes[highestResponseRatioIndex].remainingTime == 0) {
                processes[highestResponseRatioIndex].completionTime = currentTime;
                processes[highestResponseRatioIndex].turnAroundTime = calculateTurnAroundTime(processes[highestResponseRatioIndex].arrivalTime, processes[highestResponseRatioIndex].completionTime);
                processes[highestResponseRatioIndex].waitingTime = calculateWaitingTime(processes[highestResponseRatioIndex].turnAroundTime, processes[highestResponseRatioIndex].serviceTime);
                isCompleted[highestResponseRatioIndex] = true;  // 标记该进程已完成
                completed++;  // 更新已完成进程数
            }
        }
    }

    // 输出调度结果
    printf("进程\t到达时间\t服务时间\t完成时间\t周转时间\t等待时间\t响应比\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("%c\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%.2f\n",
               processes[i].name,
               processes[i].arrivalTime,
               processes[i].serviceTime,
               processes[i].completionTime,
               processes[i].turnAroundTime,
               processes[i].waitingTime,
               (float)(processes[i].waitingTime + processes[i].serviceTime) / processes[i].serviceTime);
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

    printf("测试数据1（最高响应比优先HRRN调度）：\n");
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

    printf("测试数据2（最高响应比优先HRRN调度）：\n");
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

    printf("测试数据3（最高响应比优先HRRN调度）：\n");
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

    printf("测试数据4（最高响应比优先HRRN调度）：\n");
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

    printf("测试数据5（最高响应比优先HRRN调度）：\n");
    scheduleProcesses(processes5, 6);
    printf("\n");

    return 0;
}
