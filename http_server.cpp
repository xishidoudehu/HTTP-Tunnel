// HTTPServer.cpp : �������̨Ӧ�ó������ڵ㡣
//
#include "stdafx.h"
#include "http_server.h"

bool CHttpServer::InitialHttpServer() {
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		return 0;
	}

	this->myListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->myListenSocket == INVALID_SOCKET)
	{
		printf("socket error !");
		return 0;
	}
	sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(8888);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(this->myListenSocket, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		printf("bind error !");
	}
	if (listen(this->myListenSocket, 5) == SOCKET_ERROR)
	{
		printf("listen error !");
		return 0;
	}
	return 0;
}


bool CHttpServer::RecieveHttpPacket() {
	sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr);
	char revData[10000];
	printf("�ȴ�����...\n");
	this->myClientSocket = accept(this->myListenSocket, (SOCKADDR *)&remoteAddr, &nAddrlen);
	if (this->myClientSocket == INVALID_SOCKET)
	{
		printf("accept error !");
		//continue;
	}
	printf("���ܵ�һ�����ӣ�%s \r\n", inet_ntoa(remoteAddr.sin_addr));

	int ret = recv(this->myClientSocket, revData, 10000, 0);
	if (ret > 0)
	{
		revData[ret] = 0x00;
		printf(revData);
	}
	return 0;
}


bool CHttpServer::SendHttpPacket() {
	const char * sendData = "��ã�TCP�ͻ��ˣ�\n";
	send(this->myClientSocket, sendData, strlen(sendData), 0);
	closesocket(this->myClientSocket);
	return 0;
}


bool CHttpServer::CloseHttpPacket() {
	closesocket(this->myListenSocket);
	WSACleanup();
	return 0;
}