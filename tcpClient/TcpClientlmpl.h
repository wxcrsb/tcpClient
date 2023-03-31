#pragma once

/***tcp通信中的客户端类，用户可以通过将此类文件加入项目中，新建对象，直接使用该类***/

#define MAX_RECVBUF 256  // 接收数据缓冲区大小

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
	void RecvData();               // 接收数据处理
	bool ConnectSocket();          // 连接服务端
	void SendData(const char* pBuf, int bufLen);               // 发送数据

private:
	string m_LocalIP;
	int m_Port;
	bool m_Connect;
	thread *recvDataThread;
	SOCKET m_connectSocket;
};

