#pragma once

/***tcpͨ���еĿͻ����࣬�û�����ͨ���������ļ�������Ŀ�У��½�����ֱ��ʹ�ø���***/

#define MAX_RECVBUF 256  // �������ݻ�������С

#include <WinSock2.h>
#include <iostream>
#include <thread>

#pragma comment (lib, "ws2_32.lib")
using namespace std;


class TcpClientlmpl
{
public:
	TcpClientlmpl(string ip, int port);
	~TcpClientlmpl();

public:
	void RecvData();               // �������ݴ���
	bool ConnectSocket();          // ���ӷ����
	void SendData(const char* pBuf, int bufLen);               // ��������

private:
	string m_LocalIP;
	int m_Port;
	bool m_Connect;
	thread *recvDataThread;
	SOCKET m_connectSocket;
};

