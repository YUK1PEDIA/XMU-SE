#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <string.h>
#include <mstcpip.h>
#pragma comment(lib,"Ws2_32.lib")

using namespace std;


//IP首部
typedef struct tIPPackHead
{

	BYTE ver_hlen;      //IP协议版本和IP首部长度。高4位为版本，低4位为首部的长度(单位为4bytes)
	BYTE byTOS;       //服务类型
	WORD wPacketLen; //IP包总长度。包括首部，单位为byte。[Big endian]
	WORD wSequence;    //标识，一般每个IP包的序号递增。[Big endian]

	union
	{
		WORD Flags; //标志
		WORD FragOf;//分段偏移
	};
	BYTE byTTL;         //生存时间 
	BYTE byProtocolType; //协议类型，见PROTOCOL_TYPE定义
	WORD wHeadCheckSum;    //IP首部校验和[Big endian]
	DWORD dwIPSrc;         //源地址
	DWORD dwIPDes;         //目的地址
	BYTE Options;          //选项
} IP_HEAD;

int cnt;

int DecodeIP(char* buf, int len)
{
	int n = len;
	if (n >= sizeof(IP_HEAD))
	{
		IP_HEAD iphead;
		iphead = *(IP_HEAD*)buf;

		cout << "第 " << cnt++ << " 个IP数据包信息：" << endl;


		cout << "协议版本:" << (iphead.ver_hlen >> 4) << endl;
		cout << "首部长度:" << ((iphead.ver_hlen & 0x0F) << 2) << endl;//单位为4字节
		cout << "服务类型:Priority: " << (iphead.byTOS >> 5) << ",Service: " << ((iphead.byTOS >> 1) & 0x0f) << endl;
		cout << "IP包总长度:" << ntohs(iphead.wPacketLen) << endl; //网络字节序转为主机字节序
		cout << "标识:" << ntohs(iphead.wSequence) << endl;
		cout << "标志位:" << "DF=" << ((iphead.Flags >> 14) & 0x01) << ",MF=" << ((iphead.Flags >> 13) & 0x01) << endl;
		cout << "片偏移:" << (iphead.FragOf & 0x1fff) << endl;
		cout << "生存周期:" << (int)iphead.byTTL << endl;
		cout << "协议类型:" << int(iphead.byProtocolType) << endl;
		cout << "首部校验和:" << ntohs(iphead.wHeadCheckSum) << endl;
		cout << "源地址:" << inet_ntoa(*(in_addr*)&iphead.dwIPSrc) << endl;
		cout << "目的地址:" << inet_ntoa(*(in_addr*)&iphead.dwIPDes) << endl;

		cout << "==============================================================" << endl << endl;




	}
	return 0;
}
void AutoWSACleanup()
{
	::WSACleanup();
}
int main()
{
	int n;
	WSADATA wd;
	n = WSAStartup(MAKEWORD(2, 2), &wd);
	if (n)
	{
		cout << "WSAStartup函数错误！" << endl;
		return -1;
	}
	atexit(AutoWSACleanup);
	//创建SOCKET
	SOCKET sock = socket(AF_INET, SOCK_RAW, IPPROTO_IP);
	if (sock == INVALID_SOCKET)
	{
		cout << WSAGetLastError();
		return 0;
	}
	//获取本机地址
	char  name[128];
	if (-1 == gethostname(name, sizeof(name)))
	{
		closesocket(sock);
		cout << WSAGetLastError();
		return 0;
	}
	struct hostent* pHostent;
	pHostent = gethostbyname(name);
	//绑定本地地址到SOCKET句柄
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr = *(in_addr*)pHostent->h_addr_list[0]; //IP
	addr.sin_port = 8888; //端口，IP层端口可随意填
	if (SOCKET_ERROR == bind(sock, (sockaddr*)&addr, sizeof(addr)))
	{
		closesocket(sock);
		cout << WSAGetLastError();
		return 0;
	}

	//设置该SOCKET为接收所有流经绑定的IP的网卡的所有数据，包括接收和发送的数据包
	u_long sioarg = 1;
	DWORD wt = 0;
	if (SOCKET_ERROR == WSAIoctl(sock, SIO_RCVALL, &sioarg, sizeof(sioarg), NULL, 0, &wt, NULL, NULL))
	{
		closesocket(sock);
		cout << WSAGetLastError();
		return 0;
	}
	//我们只需要接收数据，因此设置为阻塞IO，使用最简单的IO模型
	u_long bioarg = 0;
	if (SOCKET_ERROR == ioctlsocket(sock, FIONBIO, &bioarg))
	{
		closesocket(sock);
		cout << WSAGetLastError();
		return 0;
	}
	//开始接收数据
	//因为前面已经设置为阻塞IO，recv在接收到数据前不会返回。

	cnt = 1;
	char buf[65535];
	int len = 0;
	do
	{
		len = recv(sock, buf, sizeof(buf), 0);
		if (len > 0)
		{
			DecodeIP(buf, len);
		}
	} while (len > 0);
	closesocket(sock);
	return 0;
}