#include <stdio.h>
#include <stdlib.h>

// 计算最佳置换算法的缺页情况
void optimal(int page_sequence[], int sequence_length, int memory_blocks) {
    int memory[memory_blocks];
    int page_faults = 0;
    int i, j, k;

    // 初始化内存块
    for (i = 0; i < memory_blocks; i++) {
        memory[i] = -1;
    }

    // 遍历页面序列
    for (i = 0; i < sequence_length; i++) {
        int page = page_sequence[i];
        int found = 0;

        // 检查页面是否已在内存中
        for (j = 0; j < memory_blocks; j++) {
            if (memory[j] == page) {
                found = 1;
                break;
            }
        }

        // 如果页面不在内存中，发生缺页
        if (!found) {
            page_faults++;
            int farthest = i;
            int replace_index = -1;

            // 寻找未来最长时间内不会被访问的页面进行替换
            for (j = 0; j < memory_blocks; j++) {
                int found_future = 0;
                for (k = i + 1; k < sequence_length; k++) {
                    if (memory[j] == page_sequence[k]) {
                        if (k > farthest) {
                            farthest = k;
                        }
                        found_future = 1;
                        break;
                    }
                }
                if (!found_future) {
                    replace_index = j;
                    break;
                }
            }

            // 如果没有找到未来不会被访问的页面，替换最远的页面
            if (replace_index == -1) {
                for (j = 0; j < memory_blocks; j++) {
                    if (farthest == i + 1) {
                        replace_index = j;
                        break;
                    }
                    if (memory[j] == page_sequence[farthest]) {
                        replace_index = j;
                        break;
                    }
                }
            }

            // 替换页面
            memory[replace_index] = page;
        }
    }

    // 计算命中率和缺页率
    float hit_ratio = (float)(sequence_length - page_faults) / sequence_length;
    float page_fault_ratio = (float)page_faults / sequence_length;

    // 输出结果
    printf("最佳置换算法OPT：\n");
    printf("缺页数：%d\n", page_faults);
    printf("缺页率：%.2f\n", page_fault_ratio);
    printf("命中率：%.2f\n", hit_ratio);
}

// 计算先进先出算法的缺页情况
void fifo(int page_sequence[], int sequence_length, int memory_blocks) {
    int memory[memory_blocks];
    int page_faults = 0;
    int i, j;
    int front = 0;
    int rear = 0;

    // 初始化内存块
    for (i = 0; i < memory_blocks; i++) {
        memory[i] = -1;
    }

    // 遍历页面序列
    for (i = 0; i < sequence_length; i++) {
        int page = page_sequence[i];
        int found = 0;

        // 检查页面是否已在内存中
        for (j = 0; j < memory_blocks; j++) {
            if (memory[j] == page) {
                found = 1;
                break;
            }
        }

        // 如果页面不在内存中，发生缺页
        if (!found) {
            page_faults++;
            // 替换最先进入内存的页面
            memory[rear] = page;
            rear = (rear + 1) % memory_blocks;
            if (rear == front) {
                front = (front + 1) % memory_blocks;
            }
        }
    }

    // 计算命中率和缺页率
    float hit_ratio = (float)(sequence_length - page_faults) / sequence_length;
    float page_fault_ratio = (float)page_faults / sequence_length;

    // 输出结果
    printf("先进先出算法FIFO：\n");
    printf("缺页数：%d\n", page_faults);
    printf("缺页率：%.2f\n", page_fault_ratio);
    printf("命中率：%.2f\n", hit_ratio);
}

// 计算最近最少使用算法的缺页情况
void lru(int page_sequence[], int sequence_length, int memory_blocks) {
    int memory[memory_blocks];
    int page_faults = 0;
    int i, j, k;
    int use_time[memory_blocks];

    // 初始化内存块和使用时间数组
    for (i = 0; i < memory_blocks; i++) {
    memory[i] = -1;
    use_time[i] = -1;
    }

    // 遍历页面序列
    for (i = 0; i < sequence_length; i++) {
        int page = page_sequence[i];
        int found = 0;

        // 检查页面是否已在内存中
        for (j = 0; j < memory_blocks; j++) {
            if (memory[j] == page) {
                found = 1;
                use_time[j] = i;
                break;
            }
        }

        // 如果页面不在内存中，发生缺页
        if (!found) {
            page_faults++;
            int least_used = i;
            int replace_index = -1;

            // 寻找最近最少使用的页面进行替换
            for (j = 0; j < memory_blocks; j++) {
                if (use_time[j] < least_used) {
                    least_used = use_time[j];
                    replace_index = j;
                }
            }

            // 替换页面
            memory[replace_index] = page;
            use_time[replace_index] = i;
        }
    }

    // 计算命中率和缺页率
    float hit_ratio = (float)(sequence_length - page_faults) / sequence_length;
    float page_fault_ratio = (float)page_faults / sequence_length;

    // 输出结果
    printf("最近最少使用算法LRU：\n");
    printf("缺页数：%d\n", page_faults);
    printf("缺页率：%.2f\n", page_fault_ratio);
    printf("命中率：%.2f\n", hit_ratio);
}

int main() {
    int memory_blocks = 3;

    // 第一组页面序列数据及测试
    int page_sequence1[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int sequence_length1 = sizeof(page_sequence1) / sizeof(page_sequence1[0]);

    printf("对于第一组页面序列：\n");
    optimal(page_sequence1, sequence_length1, memory_blocks);
    fifo(page_sequence1, sequence_length1, memory_blocks);
    lru(page_sequence1, sequence_length1,  memory_blocks);

    // 第二组页面序列数据及测试
    int page_sequence2[] = {3, 4, 5, 6, 3, 4, 1, 3, 4, 5, 6, 1};
    int sequence_length2 = sizeof(page_sequence2) / sizeof(page_sequence2[0]);

    printf("对于第二组页面序列：\n");
    optimal(page_sequence2, sequence_length2, memory_blocks);
    fifo(page_sequence2, sequence_length2, memory_blocks);
    lru(page_sequence2, sequence_length2,  memory_blocks);

    // 第三组页面序列数据及测试
    int page_sequence3[] = {2, 3, 4, 1, 2, 3, 4, 5, 2, 3, 4, 1};
    int sequence_length3 = sizeof(page_sequence3) / sizeof(page_sequence3[0]);

    printf("对于第三组页面序列：\n");
    optimal(page_sequence3, sequence_length3, memory_blocks);
    fifo(page_sequence3, sequence_length3, memory_blocks);
    lru(page_sequence3, sequence_length3,  memory_blocks);

    // 第四组页面序列数据及测试
    int page_sequence4[] = {4, 5, 6, 7, 4, 5, 8, 4, 5, 6, 7, 8};
    int sequence_length4 = sizeof(page_sequence4) / sizeof(page_sequence4[0]);

    printf("对于第四组页面序列：\n");
    optimal(page_sequence4, sequence_length4, memory_blocks);
    fifo(page_sequence4, sequence_length4, memory_blocks);
    lru(page_sequence4, sequence_length4,  memory_blocks);

    // 第五组页面序列数据及测试
    int page_sequence5[] = {1, 3, 5, 7, 1, 3, 9, 1, 3, 5, 7, 9};
    int sequence_length5 = sizeof(page_sequence5) / sizeof(page_sequence5[0]);

    printf("对于第五组页面序列：\n");
    optimal(page_sequence5, sequence_length5, memory_blocks);
    fifo(page_sequence5, sequence_length5, memory_blocks);
    lru(page_sequence5, sequence_length5,  memory_blocks);

    return 0;
}