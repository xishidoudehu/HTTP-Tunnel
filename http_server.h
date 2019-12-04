#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WINSOCK2.H>
#include <iostream>
#include <string> 

#pragma comment(lib,"ws2_32.lib")
class CHttpServer
{
public:
	bool InitialHttpServer();
	bool RecieveHttpPacket();
	bool SendHttpPacket();
	bool CloseHttpPacket();
private:
	SOCKET myListenSocket;
	SOCKET myClientSocket;
};

