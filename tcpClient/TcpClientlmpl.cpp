#include "TcpClientlmpl.h"

TcpClientlmpl::TcpClientlmpl(string ip, int port)
{
	m_LocalIP = ip;
	m_Port = port;
	m_Connect = false;

	// tcp��ʼ��
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsadata;
	if (WSAStartup(sockVersion, &wsadata) != 0)
	{
		cout << "���������ʧ��\n";
		return;
	} 
	else
	{
		// ���ӿ�ɹ��󣬿����߳�һֱ�������ӷ����ֱ���ɹ�������
		recvDataThread = new thread(&TcpClientlmpl::RecvData, this);
	}
}

TcpClientlmpl::~TcpClientlmpl()
{
	if (recvDataThread != NULL)
	{
		recvDataThread = NULL;
		delete recvDataThread;
	}
}

void TcpClientlmpl::RecvData()
{
	while (true)
	{
		if (ConnectSocket())
		{
			char recvBuf[MAX_RECVBUF];
			memset(recvBuf, 0, MAX_RECVBUF);
			while (recv(m_connectSocket, recvBuf, MAX_RECVBUF, 0) > 0)
			{
				cout << recvBuf << endl;
			}
		} 
		else
		{
			Sleep(500);
			continue;
		}
		closesocket(m_connectSocket);
		m_connectSocket = NULL;
		Sleep(500);
	}
}

bool TcpClientlmpl::ConnectSocket()
{
	// ����socket�������ӷ����
	m_connectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_connectSocket == INVALID_SOCKET)
	{
		cout << "�����ͻ��������׽���ʧ��\n";
		closesocket(m_connectSocket);
		m_connectSocket = NULL;
		return false;
	}

	const char* pAddr = m_LocalIP.c_str();
	sockaddr_in addrConnServer;
	addrConnServer.sin_family = AF_INET;
	addrConnServer.sin_port = htons(m_Port);
	addrConnServer.sin_addr.S_un.S_addr = inet_addr(pAddr);
	if (connect(m_connectSocket, (SOCKADDR*)&addrConnServer, sizeof(addrConnServer)) == INVALID_SOCKET)
	{
		cout << "�ͻ������ӷ����ʧ��\n";
		closesocket(m_connectSocket);
		m_connectSocket = NULL;
		return false;
	} 
	else
	{
		m_Connect = true;
		cout << "�ͻ������ӷ���˳ɹ�\n";
		return true;
	}
}

void TcpClientlmpl::SendData(const char* pBuf, int bufLen)
{
	int ret = send(m_connectSocket, pBuf, bufLen, 0);
	if (ret == SOCKET_ERROR)
	{
		cout << "�ͻ��˷������ݳ���\n";
		return;
	} 
	else
	{
		cout << "�ͻ��˷������ݳɹ�\n";
		return;
	}
}
