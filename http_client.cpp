#include "stdafx.h"
#include "http_client.h"

CHttpClient::CHttpClient(IN const char *lpszCommand,
						 IN int nNetTimeout,
						 IN unsigned short nPort,
						 IN const char* lpszServerIp) {
	string strIp;
	this->myClientRequest.sCommand = lpszCommand;
	this->myNetTimeout = nNetTimeout;
	this->myPort = nPort;
	this->myServerIp = lpszServerIp;


	strIp = lpszServerIp;		//char to string for string concatenation.
	this->myClientRequest.sHost = "Host: " + strIp + ":" + to_string(myPort) + "\r\n";
	this->myClientRequest.sContent = "Full request URI: http://" + strIp + ":" + to_string(myPort) + "/sso/login.html?business=";
	this->myClientRequest.sRequest =  this->myClientRequest.sHead + this->myClientRequest.sHost + 
								      this->myClientRequest.sConnection + this->myClientRequest.sCache +
									  this->myClientRequest.sUpgrade + this->myClientRequest.sUserAgent + 
									  this->myClientRequest.sRefer + this->myClientRequest.sAccept +
									  this->myClientRequest.sCookie + this->myClientRequest.sBlank + 
									  this->myClientRequest.sContent;
	this->myRequest = this->myClientRequest.sRequest + this->myClientRequest.sCommand;
	this->mySendData = this->myRequest.data();
}


bool CHttpClient::InitialHttpClient() {
	printf("\n[*]Starting the http client.\n");
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	if (WSAStartup(sockVersion, &data) != 0)
	{
		printf("[-]WSA startup error!\n");
		return false;
	}
	this->mySocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->mySocket == INVALID_SOCKET)
	{
		printf("[-]Invalid socket!\n");
		return false;
	}
	// Set the sending time limit.
	if ((::setsockopt(this->mySocket, SOL_SOCKET, SO_SNDTIMEO, (char *)&(this->myNetTimeout), sizeof(int))) < 0) {
		printf("[-]Set send sockopt error!\n");
		return false;
	}
	// Set the receiving time limit.
	if ((::setsockopt(this->mySocket, SOL_SOCKET, SO_RCVTIMEO, (char *)&(this->myNetTimeout), sizeof(int))) < 0) {
		printf("[-]Set receive sockopt error!\n");
		return false;
	}

	SOCKET connectSocket = this->mySocket;
	sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(this->myPort);
	serAddr.sin_addr.S_un.S_addr = inet_addr(this->myServerIp);
	if (connect(connectSocket, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
	{
		printf("[-]Connect error!\n");
		return false;
	}
	printf("[+]Initial http client success!\n");
	return true;
}


bool CHttpClient::SendHttpPack() {
	SOCKET sendSocket = this->mySocket;
	printf("[+]The data packet is constructed and is being sent.\n");
	if (send(sendSocket, this->mySendData, strlen(this->mySendData), 0) == SOCKET_ERROR)
	{
		printf("[-]Send error!\n");
		return false;
	}
	printf("[+]Send http pack success!\n");
	printf(this->mySendData);
	printf("\n");
	return true;
}


int CHttpClient::RecvHttpPack() {
	SOCKET recvSocket = this->mySocket;
	char recData[10000];
	int iRetLen;
	string sNewCommand;
	printf("[*]Ready to accept the returned packet.\n");
	iRetLen = recv(recvSocket, recData, 10000, 0);
	if (iRetLen > 0 ) {
		recData[iRetLen] = 0x00;
		printf("[+]Receive http pack success!\n");
		printf(recData);
		printf("\n");
		printf("[*]Input 0 to end or new command to get more information.\n[+]Command: ");
		cin >> sNewCommand;
		if (atoi(sNewCommand.data()) != 0) {
			this->myRequest = this->myClientRequest.sRequest + sNewCommand;
			this->mySendData = this->myRequest.data();
			printf("[*]You choose to get more information.\n");
			printf("[+]Reconstructing the request packet.\n");
			printf("\n");
			return 1;
		}
		else {
			printf("[*]You choose to end.\n");
			printf("[+]Ending communication.\n");
			return 0;
		}
	}
	else {
		printf("[-]Receive error!\n");
		return -1;
	}
}


void CHttpClient::CloseSocket() {
	SOCKET cloSocket;
	cloSocket = this->mySocket;
	closesocket(cloSocket);
	WSACleanup();
	printf("[+]End success.\n");
}




/* Custom buffer size, accept packets in segments.	
 int iFlag = 1;			// Determine whether the buffer data has been read.0 end,1 go on.
 while (iFlag) {
		iRetLen = recv(recvSocket, recData, 1024, 0);
		printf("len%d", iRetLen);
		if (iRetLen < 0) {
			iFlag = 0;
			if (iRetLen == EAGAIN) {
				printf("[*]Already processed.\n");
				return 0;
			}	
			else
				printf("[-]Receive error!\n");
				return -1;
		}
		else if (iRetLen == 0) {
			iFlag = 0;
			printf("[*]The server has shut down normally.\n");
		}
		recData[iRetLen] = 0x00;
		printf(recData);
	}
	printf("\n");
	printf("[*]Input 0 to end or new command to get more information.\n[+]Command: ");
	cin >> sNewCommand;
	if (atoi(sNewCommand.data()) != 0) {
		this->myRequest = this->myClientRequest.sRequest + sNewCommand;
		this->mySendData = this->myRequest.data();
		printf("[*]You choose to get more information.\n");
		printf("[+]Reconstructing the request packet.\n");
		return 1;
	}
	else {
		printf("[*]You choose to end.\n");
		printf("[+]Ending communication.\n");
		return 0;
	}*/