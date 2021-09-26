#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "mysnapper.h"
#include <iostream>

using namespace std;

#define       SIO_RCVALL       _WSAIOW(IOC_VENDOR,1)

mySnapper::mySnapper() 
{
	int err = WSAStartup(wVersion,&wsaData);

	if (0 != err) 
	{
		throw exception( "初始化winsock库失败");
		
	}
	servSocket = socket(PF_INET, SOCK_RAW, IPPROTO_IP);
}

void mySnapper::createSocket() 
{
	char hostname[100];
	struct hostent *local;
	struct in_addr myaddr;

	if (gethostname(hostname, sizeof(hostname)) == SOCKET_ERROR)
	{
		printf("Error : %d", WSAGetLastError());
		return;
	}
	printf("\nHost name : %s \n", hostname);

	local = gethostbyname("localhost");
	printf("\nAvailable Network Interfaces : \n");
	if (local == NULL) 
	{
		printf("Error : %d.\n", WSAGetLastError());
		return ;
	}

	for (int i = 0; local->h_addr_list[i] != 0; ++i)
	{
		memcpy(&myaddr, local->h_addr_list[i], sizeof(struct in_addr));
		printf("Interface Number : %d Address : %s\n", i, inet_ntoa(myaddr));
	}

	int in = 0;
	sockaddr_in dest;
	memset(&dest, 0, sizeof(dest));
	memcpy(&dest.sin_addr.s_addr, local->h_addr_list[in], sizeof(dest.sin_addr.s_addr));
		//myaddr.sin_addr = *(in_addr*)pHostent->h_addr_list[0];
	dest.sin_family = AF_INET;
	dest.sin_port = htons(0);

		if (bind(servSocket, (SOCKADDR *)&dest, sizeof(dest)) == SOCKET_ERROR)
		{
			closesocket(servSocket);
			cout << "套接字创建失败:bind执行失败:"<<WSAGetLastError()<<endl;
		}
		else 
		{
			setGetAllDataPag();
		}
}

void mySnapper::setGetAllDataPag() 
{
	DWORD dwBufferLen[10] = { 0 };
	DWORD dwBufferInLen = 1;
	DWORD dwBytesReturned = 0;

	printf("\nSetting socket to sniff...\n");
	int iRet = WSAIoctl(servSocket, SIO_RCVALL, &dwBufferInLen, sizeof(dwBufferInLen),
		&dwBufferLen, sizeof(dwBufferLen), &dwBytesReturned, NULL, NULL);

	if (iRet!= 0)
	{
		printf("设置接收网卡的所有数据，包括发送和接收数据包失败 %d\n" , WSAGetLastError());
		closesocket(servSocket);
	}
}

void mySnapper::getData() 
{
	int len = 0;
	listen(servSocket, 5);

	char strFromIp[16] = { 0 }, strCurTime[32] = { 0 };
	char strBuffer[1024 * 10], strData[4096] = { 0 };
	sockaddr_in addrFrom;
	int fromLen = sizeof(addrFrom);
	TCPHeader tcpData;
	NetData netData;
	IPHeader ipHeader;
	int cnt = 0;
	do 
	{
		cnt += 1;
		memset(&ipHeader, 0, sizeof(IPHeader));
		len = recvfrom(servSocket, strBuffer, sizeof(strBuffer),0, (sockaddr*)&addrFrom, &fromLen);

		if (len > 0) 
		{
			memcpy(&ipHeader, strBuffer, sizeof(ipHeader));


			if (ipHeader.Protocol == IPPROTO_TCP) 
			{
				memcpy(&tcpData, strBuffer + sizeof(IPHeader), sizeof(tcpData));
				int iSrcPort = tcpData.SrcPort;
				int iDstPort = tcpData.DstPort;
				memcpy(&netData, strBuffer + sizeof(IPHeader) + sizeof(tcpData), sizeof(netData));
				printf("Message form server:%d,srcPort:%d,desport: %d\n", len, iSrcPort, iDstPort);
				if (cnt %3==0)
					printf("data : %s\n", netData.strData);
				//if (tcp->dport == 1234 || tcp->dport == 1234 )
				//{

				//	printf("Message form server:%d,srcPort:%s,desport: %d\n", len, tcp->sport, tcp->dport);
				//}

			}
		}
	} while (len > 0);
}
 
char* mySnapper::intIpToStr(unsigned int ip)
{
	char* str = (char*)malloc(16);
	memset(str, 0, 16);
	uint32_t num = 0;


	int i = 0;
	for (i = 0; i < 4; i++)
	{
		num = (ip & (255 << ((3 - i) * 8))) >> ((3 - i) * 8);
		fill_str(num, str + i * 4);
		if (i == 3) break;
		str[i * 4 + 4 - 1] = '.';
	}
	return str;
}

void mySnapper::fill_str(uint32_t num, char* str)
{
	str[0] = num / 100 + '0';
	str[1] = num % 100 / 10 + '0';
	str[2] = num % 10 + '0';
}

mySnapper::~mySnapper() 
{
	WSACleanup();
	closesocket(servSocket);
}
