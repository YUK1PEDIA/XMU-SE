/*
 * Copyright (c) 1999 - 2005 NetGroup, Politecnico di Torino (Italy)
 * Copyright (c) 2005 - 2006 CACE Technologies, Davis (California)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Politecnico di Torino, CACE Technologies
 * nor the names of its contributors may be used to endorse or promote
 * products derived from this software without specific prior written
 * permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#define WIN32  
#include <pcap.h>  
#pragma comment (lib,"wpcap.lib")
#pragma comment(lib, "ws2_32.lib")
#ifdef _MSC_VER
 /*
  * we do not want the warnings about the old deprecated and unsecure CRT functions
  * since these examples can be compiled under *nix as well
  */
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "pcap.h"
#include<string.h>

  /* 4 bytes IP address */
typedef struct ip_address
{
	u_char byte1;
	u_char byte2;
	u_char byte3;
	u_char byte4;
}ip_address;

/* IPv4 header */
typedef struct ip_header
{
	u_char	ver_ihl;		// Version (4 bits) + Internet header length (4 bits)
	u_char	tos;			// Type of service 
	u_short tlen;			// Total length 
	u_short identification; // Identification
	u_short flags_fo;		// Flags (3 bits) + Fragment offset (13 bits)
	u_char	ttl;			// Time to live
	u_char	proto;			// Protocol
	u_short crc;			// Header checksum
	ip_address	saddr;		// Source address
	ip_address	daddr;		// Destination address
	u_int	op_pad;			// Option + Padding
}ip_header;

/* UDP header*/
typedef struct udp_header
{
	u_short sport;			// Source port
	u_short dport;			// Destination port
	u_short len;			// Datagram length
	u_short crc;			// Checksum
}udp_header;

typedef struct {
	u_char dest_addr[6];
	u_char src_addr[6];
	u_char type[2];
}mac_header;

/* prototype of the packet handler */
void packet_handler(u_char* param, const struct pcap_pkthdr* header, const u_char* pkt_data);
#define from_NIC  //去掉注释就是网卡模式,混合模式可以捕获任何包

int main()
{
	pcap_if_t* alldevs;
	pcap_if_t* d;
	int inum;
	int i = 0;
	pcap_t* adhandle;
	char errbuf[PCAP_ERRBUF_SIZE];
	u_int netmask;
	char packet_filter[] = "ip and udp ";
	//	char packet_filter[] = "arp ";
	//	char packet_filter[] = "icmp";  //一定要注意，如果只是IP和UDP，会把其他的包譬如ARP过滤掉、可以设为空字符串
	struct bpf_program fcode;
#ifdef from_NIC



	/* Retrieve the device list */
	if (pcap_findalldevs(&alldevs, errbuf) == -1)
	{
		fprintf(stderr, "Error in pcap_findalldevs: %s\n", errbuf);
		exit(1);
	}

	/* Print the list */
	for (d = alldevs; d; d = d->next)
	{
		printf("%d. %s", ++i, d->name);
		if (d->description)
			printf(" (%s)\n", d->description);
		else
			printf(" (No description available)\n");
	}

	if (i == 0)
	{
		printf("\nNo interfaces found! Make sure WinPcap is installed.\n");
		return -1;
	}

	printf("Enter the interface number (1-%d):", i);
	scanf("%d", &inum);

	/* Check if the user specified a valid adapter */
	if (inum < 1 || inum > i)
	{
		printf("\nAdapter number out of range.\n");

		/* Free the device list */
		pcap_freealldevs(alldevs);
		return -1;
	}

	/* Jump to the selected adapter */
	for (d = alldevs, i = 0; i < inum - 1; d = d->next, i++);

	/* Open the adapter */
	if ((adhandle = pcap_open_live(d->name,	// name of the device
		65536,			// portion of the packet to capture. 
					   // 65536 grants that the whole packet will be captured on all the MACs.
		1,				// promiscuous mode (nonzero means promiscuous)
		1000,			// read timeout
		errbuf			// error buffer
	)) == NULL)
	{
		fprintf(stderr, "\nUnable to open the adapter. %s is not supported by WinPcap\n");
		/* Free the device list */
		pcap_freealldevs(alldevs);
		return -1;
	}

	/* Check the link layer. We support only Ethernet for simplicity. */
	if (pcap_datalink(adhandle) != DLT_EN10MB)
	{
		fprintf(stderr, "\nThis program works only on Ethernet networks.\n");
		/* Free the device list */
		pcap_freealldevs(alldevs);
		return -1;
	}

	if (d->addresses != NULL)
		/* Retrieve the mask of the first address of the interface */
		netmask = ((struct sockaddr_in*)(d->addresses->netmask))->sin_addr.S_un.S_addr;
	else
		/* If the interface is without addresses we suppose to be in a C class network */
		netmask = 0xffffff;


	//compile the filter 
	if (pcap_compile(adhandle, &fcode, packet_filter, 1, netmask) < 0)
	{
		fprintf(stderr, "\nUnable to compile the packet filter. Check the syntax.\n");
		/* Free the device list */
		pcap_freealldevs(alldevs);
		return -1;
	}

	//set the filter
	if (pcap_setfilter(adhandle, &fcode) < 0)
	{
		fprintf(stderr, "\nError setting the filter.\n");
		/* Free the device list */
		pcap_freealldevs(alldevs);
		return -1;
	}

	printf("\nlistening on %s...\n", d->description);

	/* At this point, we don't need any more the device list. Free it */
	pcap_freealldevs(alldevs);

	/* start the capture */
	pcap_loop(adhandle, 0, packet_handler, NULL);
#else//如果调试，就注释掉define的from_NIC 在wireshark中抓到包，导出到文件夹，用pcap_open_offline读取pcap文件即可。
	/* Open the capture file */
	if ((adhandle = pcap_open_offline("C:\\Users\\刘云龙\\Desktop\\dns.pcap",			// name of the device 修改文件路径 刚才从wireshark上捕获出存的pcap包的路径，而不是argv[1]
		errbuf					// error buffer
	)) == NULL)
	{
		fprintf(stderr, "\nUnable to open the file \n");
		return -1;
	}

	/* read and dispatch packets until EOF is reached */
	pcap_loop(adhandle, 0, packet_handler, NULL);

	pcap_close(adhandle);



#endif




	return 0;
}

/* Callback function invoked by libpcap for every incoming packet */
void packet_handler(u_char* param, const struct pcap_pkthdr* header, const u_char* pkt_data)
{

	struct tm* ltime;
	char timestr[16];
	ip_header* ih;
	udp_header* uh;
	mac_header* mh;
	u_int ip_len;
	u_short sport, dport;
	time_t local_tv_sec;

	/*
	 * unused parameter
	 */
	(VOID)(param);

	/* convert the timestamp to readable format */
	local_tv_sec = header->ts.tv_sec;//帧到达的时间
	ltime = localtime(&local_tv_sec);
	strftime(timestr, sizeof timestr, "%H:%M:%S", ltime);

	/* print timestamp and length of the packet */
	printf("%s.%.6d len:%d\n ", timestr, header->ts.tv_usec, header->len);

	/* retireve the position of the ip header */
	ih = (ip_header*)(pkt_data +
		14); //length of ethernet header
	mh = (mac_header*)pkt_data;

	/* retireve the position of the udp header */
	ip_len = (ih->ver_ihl & 0xf) * 4;
	uh = (udp_header*)((u_char*)ih + ip_len);

	/* convert from network byte order to host byte order */
	sport = ntohs(uh->sport);//端口号 networktohos
	dport = ntohs(uh->dport);//端口号

	int length = sizeof(mac_header) + sizeof(ip_header);


	if (mh->type[1] == 0 && mh->type[0] == 8)//08 00    0001
	{
		printf("get an ip packet\n");
		if (ih->proto == 0x0001) {
			printf("get an icmp packet\n");
		}
	}
	else if (mh->type[1] == 6 && mh->type[0] == 8)//0806
		printf("get an arp packet\n");

	//printf("type:%02x %02x\n", mh->type[1],mh->type[0]);  //ntohs  返回的是short int 2B 65535max

	printf("DEST MAC:");
	for (int i = 0; i < 6; i++) {
		if (i != 5)
			printf("%02x:", mh->dest_addr[i]);
		else
			printf("%02x\n", mh->dest_addr[i]);
	}

	printf(" SRC MAC:");
	for (int i = 0; i < 6; i++) {
		if (i != 5)
			printf("%02x:", mh->src_addr[i]);
		else
			printf("%02x\n", mh->src_addr[i]);
	}





	/* print ip addresses and udp ports */
	//printf("%d.%d.%d.%d.%d -> %d.%d.%d.%d.%d\n",
	//	ih->saddr.byte1,
	//	ih->saddr.byte2,
	//	ih->saddr.byte3,
	//	ih->saddr.byte4,
	//	sport,
	//	ih->daddr.byte1,
	//	ih->daddr.byte2,
	//	ih->daddr.byte3,
	//	ih->daddr.byte4,
	//	dport);//指定出ih的saddr的bytei即可确定sender的ip是多少才输出之类的

	printf("\n\n\n\n\n");


	//抓完了写入文件
		// 写文件
	FILE* fp = fopen("data.csv", "a+");
	fprintf(fp, "time:,%s\n", timestr);
	fprintf(fp, "src_mac:,");
	for (int i = 0; i < 6; i++) {
		if (i != 5)
			fprintf(fp, "%02x:", mh->src_addr[i]);
		else
			fprintf(fp, "%02x\n", mh->src_addr[i]);
	}
	fprintf(fp, "dest_mac:,");
	for (int i = 0; i < 6; i++) {
		if (i != 5)
			fprintf(fp, "%02x:", mh->dest_addr[i]);
		else
			fprintf(fp, "%02x\n", mh->dest_addr[i]);
	}
	fprintf(fp, "len:,%d\n\n\n", header->len);

	fclose(fp);
}









