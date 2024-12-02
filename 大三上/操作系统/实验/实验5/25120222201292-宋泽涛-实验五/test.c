#include <stdio.h>
#include <stdbool.h>

#define PROCESS_COUNT 5   // 进程数
#define RESOURCE_COUNT 3  // 资源种类数

// 全局变量
int available[RESOURCE_COUNT];          // 可用资源向量
int maximum[PROCESS_COUNT][RESOURCE_COUNT]; // 每个进程的最大需求矩阵
int allocation[PROCESS_COUNT][RESOURCE_COUNT]; // 当前资源分配矩阵
int need[PROCESS_COUNT][RESOURCE_COUNT];  // 每个进程的剩余需求矩阵

// 初始化资源、需求和分配矩阵
void initialize() {
    // 初始化可用资源向量
    available[0] = 3; available[1] = 3; available[2] = 2;
    
    // 初始化每个进程的最大需求矩阵
    int max[PROCESS_COUNT][RESOURCE_COUNT] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };
    
    // 初始化当前的资源分配矩阵
    int alloc[PROCESS_COUNT][RESOURCE_COUNT] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };
    
    // 计算每个进程的剩余需求矩阵
    for (int i = 0; i < PROCESS_COUNT; i++) {
        for (int j = 0; j < RESOURCE_COUNT; j++) {
            maximum[i][j] = max[i][j];
            allocation[i][j] = alloc[i][j];
            need[i][j] = maximum[i][j] - allocation[i][j]; // 计算剩余需求
        }
    }
}

bool check_safety() {
    int work[RESOURCE_COUNT]; // 工作向量，模拟系统的临时资源状态
    bool finish[PROCESS_COUNT] = {0}; // 每个进程的完成状态
    int safeSequence[PROCESS_COUNT]; // 安全序列
    int count = 0; // 安全序列中的进程计数
    
    // 初始化工作向量为当前可用资源
    for (int i = 0; i < RESOURCE_COUNT; i++)
        work[i] = available[i];
    
    // 找到一个可满足条件的进程，并更新系统状态，直到找不到为止
    while (count < PROCESS_COUNT) {
        bool found = false;
        for (int p = 0; p < PROCESS_COUNT; p++) {
            if (finish[p] == 0) { // 检查是否完成
                int j;
                for (j = 0; j < RESOURCE_COUNT; j++)
                    if (need[p][j] > work[j]) // 检查资源是否满足需求
                        break;

                if (j == RESOURCE_COUNT) { // 所有资源都满足需求
                    for (int k = 0; k < RESOURCE_COUNT; k++)
                        work[k] += allocation[p][k]; // 释放资源到工作向量

                    safeSequence[count++] = p; // 记录安全序列
                    finish[p] = 1; // 标记为完成
                    found = true; // 表示找到一个满足条件的进程
                }
            }
        }

        if (found == false) { 
            printf("系统处于不安全状态\n");
            return false;
        }
    }

    // 如果系统安全，输出安全序列
    printf("系统处于安全状态，安全序列为: ");
    for (int i = 0; i < PROCESS_COUNT; i++)
        printf("%d ", safeSequence[i]);
    printf("\n");
    return true;
}

// 资源请求处理函数，根据请求判断是否分配资源
bool request_resources(int p, int req[]) {
    // 检查请求是否超过进程的最大需求
    for (int i = 0; i < RESOURCE_COUNT; i++) {
        if (req[i] > need[p][i]) {
            printf("进程%d请求超过其最大需求量！\n", p);
            return false;
        }
    }
    
    // 检查请求的资源是否可用
    for (int i = 0; i < RESOURCE_COUNT; i++) {
        if (req[i] > available[i]) {
            printf("资源不足，进程%d需等待\n", p);
            return false;
        }
    }

    // 暂时分配资源并更新系统状态
    for (int i = 0; i < RESOURCE_COUNT; i++) {
        available[i] -= req[i];
        allocation[p][i] += req[i];
        need[p][i] -= req[i];
    }

    // 检查系统是否处于安全状态
    if (check_safety()) return true;

    // 如果不安全，撤销资源分配，恢复状态
    for (int i = 0; i < RESOURCE_COUNT; i++) {
        available[i] += req[i];
        allocation[p][i] -= req[i];
        need[p][i] += req[i];
    }
    
    printf("请求被拒绝，恢复系统状态\n");
    return false;
}

int main() {
    initialize();
    
    int req1[RESOURCE_COUNT] = {1, 0, 2};  // P1请求资源
    printf("进程P1请求{1, 0, 2}:\n");
    if (request_resources(1, req1))
        printf("P1资源分配成功\n");
    else
        printf("P1资源分配失败\n");
    
    int req2[RESOURCE_COUNT] = {3, 3, 0};  // P0请求资源
    printf("进程P0请求{3, 3, 0}:\n");
    if (request_resources(0, req2))
        printf("P0资源分配成功\n");
    else
        printf("P0资源分配失败\n");
    
    int req3[RESOURCE_COUNT] = {2, 0, 1};  // P2请求资源
    printf("进程P2请求{2, 0, 1}:\n");
    if (request_resources(2, req3))
        printf("P2资源分配成功\n");
    else
        printf("P2资源分配失败\n");
    
    int req4[RESOURCE_COUNT] = {0, 2, 0};  // P3请求资源
    printf("进程P3请求{0, 2, 0}:\n");
    if (request_resources(3, req4))
        printf("P3资源分配成功\n");
    else
        printf("P3资源分配失败\n");
    
    int req5[RESOURCE_COUNT] = {3, 3, 3};  // P4请求资源
    printf("进程P4请求{3, 3, 3}:\n");
    if (request_resources(4, req5))
        printf("P4资源分配成功\n");
    else
        printf("P4资源分配失败\n");
    
    return 0;
}
