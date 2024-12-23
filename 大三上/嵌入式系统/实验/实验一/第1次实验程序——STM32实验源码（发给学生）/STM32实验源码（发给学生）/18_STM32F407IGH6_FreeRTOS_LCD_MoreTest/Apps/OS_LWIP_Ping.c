/*
 * @Author: your name
 * @Date: 2021-07-12 15:08:22
 * @LastEditTime: 2021-07-12 19:03:21
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \MDK-ARMd:\Project\stm32-Project\STM32F407IGT6_FreeRTOS_LCD_MoreTest\Apps\OS_LWIP_Ping.c
 */
#include "OS_LWIP_Ping.h"
#include "ip.h"

struct raw_pcb *ping_pcb;

// 创建ICMP控制块
uint8_t icmp_pcb_init(void)
{
  ping_pcb = raw_new(IP_PROTO_ICMP);
  if(!ping_pcb)
    return 1;
  return 0;
}
// 示例： ping_send(192,168,0,111);
uint8_t ping_send(uint8_t a, uint8_t b, uint8_t c, uint8_t d)
{
  struct pbuf *p;
  ip_addr_t ipaddr;
  struct icmp_echo_hdr *iecho;
  err_t err;

  IP_ADDR4(&ipaddr, a, b, c, 222);//在这里改成你单片机的IP地址
  ip_addr_set(&ping_pcb->local_ip, &ipaddr);//本机IP

  IP_ADDR4(&ipaddr, a, b, c, d);//在这里改成你想ping的IP地址
  ip_addr_set(&ping_pcb->remote_ip, &ipaddr);//远端IP

  p = pbuf_alloc(PBUF_IP, sizeof(struct icmp_echo_hdr), PBUF_RAM);
  if(!p)
  {
    return 1;
  }

  iecho = (struct icmp_echo_hdr *)p->payload;
  iecho->type = 8;
  iecho->code = 0;
  iecho->id =htons(0x0200);
  iecho->seqno =htons(0x5800);
  iecho->chksum = 0;
  //iecho->chksum = inet_chksum(p->payload, sizeof(struct icmp_echo_hdr));//这里需要注释掉，否则会ping失败

  err = raw_sendto(ping_pcb, p, &ping_pcb->remote_ip);//发送ping包
  if( err != ERR_OK )
  {
    return 1;
  }
  pbuf_free(p);

  return 0;
}

