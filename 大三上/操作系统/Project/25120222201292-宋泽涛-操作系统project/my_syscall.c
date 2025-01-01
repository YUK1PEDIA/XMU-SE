#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/uaccess.h>

SYSCALL_DEFINE2(my_syscall, char __user *, buffer, size_t, len) {
    const char *message = "Hello, world!";
    size_t message_len = strlen(message) + 1;  // 包括字符串末尾的 '\0'

    // 检查用户缓冲区的长度是否足够
    if (len < message_len) {
        printk(KERN_WARNING "Buffer size is too small!\n");
        return -EINVAL;
    }

    // 将字符串拷贝到用户空间
    if (copy_to_user(buffer, message, message_len)) {
        printk(KERN_WARNING "Failed to copy data to user space!\n");
        return -EFAULT;
    }

    printk(KERN_INFO "String successfully copied to user space!\n");
    return 0;
}
