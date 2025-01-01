#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <errno.h>

#define MY_SYSCALL 440  // 系统调用号

int main() {
    char buffer[128];  // 用于存储返回的字符串
    size_t buffer_size = sizeof(buffer);

    // 调用系统调用
    long ret = syscall(MY_SYSCALL, buffer, buffer_size);

    if (ret == 0) {
        printf("System call succeeded! Message: %s\n", buffer);
    } else {
        printf("System call failed with error: %ld, errno: %d\n", ret, errno);
    }

    return 0;
}
