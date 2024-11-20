#ifndef __OS_LWIP_PING_H__
#define __OS_LWIP_PING_H__

#include <stdio.h>
#include "main.h"
#include "lwip.h"
#include "lwip/raw.h"
#include "lwip/icmp.h"
#include "lwip/arch.h"
#include "lwip/ip4_addr.h"
#include "lwip/ip_addr.h"

uint8_t icmp_pcb_init(void);

uint8_t ping_send(uint8_t a, uint8_t b, uint8_t c, uint8_t d);

extern volatile unsigned char pingEchoReply;			// 定义在lwip/icmp.c文件中
#endif

