#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BLOCK_SIZE 2048         // 每块2K大小
#define NUM_BLOCKS 500          // 总共500块
#define MAX_FILES 50            // 最多文件数

// 文件结构体
typedef struct {
    char name[20];             // 文件名
    int size;                 // 文件大小（单位：字节）
    int start_block;          // 起始块号
    int blocks_used;          // 占用块数
} File;

// 全局变量
int bit_table[NUM_BLOCKS] = {0};   // 位表，0表示空闲，1表示占用
File files[MAX_FILES];            // 文件数组
int file_count = 0;               // 当前文件数量

// 分配磁盘块函数
int allocate_blocks(int size) {
    int blocks_needed = (size + BLOCK_SIZE - 1) / BLOCK_SIZE; // 需要的块数
    int start = -1;
    int count = 0;

    for (int i = 0; i < NUM_BLOCKS; i++) {
        if (bit_table[i] == 0) {
            if (start == -1) start = i;
            count++;
            if (count == blocks_needed) {
                for (int j = start; j < start + blocks_needed; j++)
                    bit_table[j] = 1; // 标记块为占用
                return start;
            }
        } else {
            start = -1;
            count = 0;
        }
    }
    return -1; // 没有足够的空间
}

// 创建文件函数
void create_file(char *name, int size) {
    int start_block = allocate_blocks(size);
    if (start_block == -1) {
        printf("Error: Not enough space to create file %s\n", name);
        return;
    }
    strcpy(files[file_count].name, name);
    files[file_count].size = size;
    files[file_count].start_block = start_block;
    files[file_count].blocks_used = (size + BLOCK_SIZE - 1) / BLOCK_SIZE;
    file_count++;
    printf("File %s created. Start block: %d, Size: %d bytes\n", name, start_block, size);
}

// 删除文件函数
void delete_file(char *name) {
    for (int i = 0; i < file_count; i++) {
        if (strcmp(files[i].name, name) == 0) {
            for (int j = files[i].start_block; j < files[i].start_block + files[i].blocks_used; j++)
                bit_table[j] = 0; // 释放磁盘块
            printf("File %s deleted.\n", name);
            files[i] = files[file_count - 1]; // 用最后一个文件覆盖删除的文件
            file_count--;
            return;
        }
    }
    printf("Error: File %s not found.\n", name);
}

// 显示当前文件分配表
void show_file_table() {
    printf("\nFile Allocation Table:\n");
    printf("Name\tStart Block\tSize\tBlocks Used\n");
    for (int i = 0; i < file_count; i++) {
        printf("%s\t%d\t%d\t%d\n", files[i].name, files[i].start_block, files[i].size, files[i].blocks_used);
    }
}

// 显示位表状态
void show_bit_table() {
    printf("\nBit Table (0: Free, 1: Used):\n");
    for (int i = 0; i < NUM_BLOCKS; i++) {
        printf("%d", bit_table[i]);
        if ((i + 1) % 50 == 0) printf("\n");
    }
    printf("\n");
}

int main() {
    srand(time(NULL));

    printf("Creating 50 files...\n");
    for (int i = 0; i < 50; i++) {
        char name[20];
        sprintf(name, "%d.txt", i + 1);
        int size = 2048 + rand() % 8192; // 文件大小2K到10K
        create_file(name, size);
    }

    show_file_table();
    show_bit_table();

    printf("\nDeleting odd-numbered files...\n");
    for (int i = 0; i < 50; i += 2) {
        char name[20];
        sprintf(name, "%d.txt", i + 1);
        delete_file(name);
    }

    show_file_table();
    show_bit_table();

    printf("\nCreating 5 new files...\n");
    create_file("A.txt", 7 * 1024);
    create_file("B.txt", 5 * 1024);
    create_file("C.txt", 2 * 1024);
    create_file("D.txt", 9 * 1024);
    create_file("E.txt", 3.5 * 1024);

    show_file_table();
    show_bit_table();

    return 0;
}
