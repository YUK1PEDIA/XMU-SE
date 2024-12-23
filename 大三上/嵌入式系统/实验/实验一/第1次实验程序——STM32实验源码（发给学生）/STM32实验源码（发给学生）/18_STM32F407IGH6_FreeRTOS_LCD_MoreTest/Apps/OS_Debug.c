/*
 * @Author: your name
 * @Date: 2021-07-07 15:34:41
 * @LastEditTime: 2021-07-12 10:32:16
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\STM32F407IGT6_FreeRTOS_LCD_MoreTest\Apps\OS_Debug.c
 */
#include "OS_Debug.h"
#include "usart.h"
#include "ff.h"

/**
 * @description: Printf重定向函数
 * @param {int} ch
 * @param {FILE} *f
 * @return {ch: 当前字节}
 */
int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&USART_DEBUG_PORT, (uint8_t *)&ch, 1, 0xFFFF);
  return ch;
}
void Printf_File_Error_Msg(uint8_t res)
{
  switch(res) {
  case FR_OK:
    CONSOLE_INFO("File 成功");
    break;
  case FR_DISK_ERR:
    CONSOLE_ERROR("File 低级别硬盘I/O层发生硬错误");
    break;
  case FR_INT_ERR:
    CONSOLE_ERROR("File 断言失败");
    break;
  case FR_NOT_READY:
    CONSOLE_ERROR("File 物理驱动器不能工作, 物理驱动器开没有准备好");
    break;
  case FR_NO_FILE:
    CONSOLE_ERROR("File 找不到文件");
    break;
  case FR_NO_PATH:
    CONSOLE_ERROR("File 找不到路径");
    break;
  case FR_INVALID_NAME:
    CONSOLE_ERROR("File 路径名格式无效");
    break;
  case FR_DENIED:
    CONSOLE_ERROR("File 由于禁止访问或目录满而拒绝访问  ");
    break;
  case FR_EXIST:
    CONSOLE_ERROR("File 由于禁止访问而拒绝访问");
    break;
  case FR_INVALID_OBJECT:
    CONSOLE_ERROR("File 文件/目录对象无效");
    break;
  case FR_WRITE_PROTECTED:
    CONSOLE_ERROR("File 物理驱动器写保护");
    break;
  case FR_INVALID_DRIVE:
    CONSOLE_ERROR("File 逻辑驱动器号无效");
    break;
  case FR_NOT_ENABLED:
    CONSOLE_ERROR("File 体积没有工作面积");
    break;
  case FR_NO_FILESYSTEM:
    CONSOLE_ERROR("File 没有有效的FAT卷");
    break;
  case FR_MKFS_ABORTED:
    CONSOLE_ERROR("File 由于任何问题，f_mkfs()被中止");
    break;
  case FR_TIMEOUT:
    CONSOLE_ERROR("File 无法在规定的期限内获得访问该卷的授权 ");
    break;
  case FR_LOCKED:
    CONSOLE_ERROR("File 根据文件共享策略，该操作被拒绝");
    break;
  case FR_NOT_ENOUGH_CORE:
    CONSOLE_ERROR("File 无法分配LFN工作缓冲区");
    break;
  case FR_TOO_MANY_OPEN_FILES:
    CONSOLE_ERROR("File 打开的文件数> FS LOCK");
    break;
  case FR_INVALID_PARAMETER:
    CONSOLE_ERROR("File 给定参数无效");
    break;
  }
}

