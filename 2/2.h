#pragma once
#ifndef MYSNAPPER_H
#define MYSNAPPER_H
#include <stdio.h>

#include "IPCommon.h"
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

class mySnapper 
{
public:
	mySnapper();
	~mySnapper();
	void createSocket();
	void getData();
private:
	void setGetAllDataPag();
	bool filterIp(IPHeader *ipHeader);
	static char* intIpToStr(unsigned int ip);
	static void fill_str(unsigned int num, char* str);

	WORD wVersion = MAKEWORD(2,2);
	WSADATA wsaData;
	SOCKET servSocket;

	unsigned long m_rawSock;
	unsigned long m_desIP;
	unsigned long m_srcIP;
	unsigned short m_desPort;
	unsigned short m_srcPort;
	unsigned long m_filterIP;
	unsigned long m_rawSocks;
	unsigned short m_filterPort;
};

#endif // !MYSOCKET_H
#pragma once

