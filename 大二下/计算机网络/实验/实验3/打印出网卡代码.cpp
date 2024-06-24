#include <iostream>
#include <vector>
#include <WinSock2.h>
#include <Iphlpapi.h>
#include <pcap.h>
#pragma comment(lib,"Iphlpapi.lib") //需要Iphlpapi.lib库 ,devc++中 项目 -> 项目选项-> 参数 -> 添加链接库 libiphlpapi.a （D:\Program Files (x86)\Dev-Cpp\MinGW64\x86_64-w64-mingw32\lib\libiphlpapi.a） 
using namespace std;

static const  int ADAPTERNUM = 10;
void getAllAdapterInfo() {

	PIP_ADAPTER_INFO pIpAdapterInfo = new IP_ADAPTER_INFO[ADAPTERNUM];// 10个网卡空间 足够了 
	unsigned long stSize = sizeof(IP_ADAPTER_INFO) * ADAPTERNUM;
	// 获取所有网卡信息，参数二为输入输出参数 
	int nRel = GetAdaptersInfo(pIpAdapterInfo, &stSize);
	// 空间不足
	if (ERROR_BUFFER_OVERFLOW == nRel) {
		// 释放空间
		if (pIpAdapterInfo != NULL)
			delete[] pIpAdapterInfo;
		return;
	}

	PIP_ADAPTER_INFO cur = pIpAdapterInfo;
	// 多个网卡 通过链表形式链接起来的 
	while (cur) {
		cout << "网卡描述：" << cur->Description << endl;
		switch (cur->Type) {
		case MIB_IF_TYPE_OTHER:
			break;
		case MIB_IF_TYPE_ETHERNET:
		{
			IP_ADDR_STRING* pIpAddrString = &(cur->IpAddressList);
			cout << "IP:" << pIpAddrString->IpAddress.String << endl;
			cout << "子网掩码:" << pIpAddrString->IpMask.String << endl;
		}
		break;
		case MIB_IF_TYPE_TOKENRING:
			break;
		case MIB_IF_TYPE_FDDI:
			break;
		case MIB_IF_TYPE_PPP:
			break;
		case MIB_IF_TYPE_LOOPBACK:
			break;
		case MIB_IF_TYPE_SLIP:
			break;
		default://无线网卡,Unknown type
		{
			IP_ADDR_STRING* pIpAddrString = &(cur->IpAddressList);
			cout << "IP:" << pIpAddrString->IpAddress.String << endl;
			cout << "子网掩码:" << pIpAddrString->IpMask.String << endl;
		}
		break;
		}
		char hex[16] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };

		// mac 地址一般6个字节 
		// mac 二进制转16进制字符串
		char macStr[18] = { 0 };//12+5+1
		int k = 0;
		for (int j = 0; j < cur->AddressLength; j++) {
			macStr[k++] = hex[(cur->Address[j] & 0xf0) >> 4];
			macStr[k++] = hex[cur->Address[j] & 0x0f];
			macStr[k++] = '-';
		}
		macStr[k - 1] = 0;

		cout << "MAC:" << macStr << endl; // mac地址 16进制字符串表示 
		cur = cur->Next;
		cout << "--------------------------------------------------" << endl;
	}

	// 释放空间
	if (pIpAdapterInfo != NULL)
		delete[] pIpAdapterInfo;
}
int main(int argc, char* argv[])
{
	getAllAdapterInfo();
	return 0;
}

