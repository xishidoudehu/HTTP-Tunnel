#include "stdafx.h"
#include "http_client.h"


int main(int argc, char *argv[]) {
	const char *lpszCommand = argv[1];		// 1
	int nNetTimeout = atoi(argv[2]);		// 1000
	unsigned short nPort = atoi(argv[3]);	// 6665
	const char *lpszServerIp = argv[4];		// 192.168.8.101
	int iFlag = 1;
	CHttpClient demo(lpszCommand, nNetTimeout, nPort, lpszServerIp);

	while (iFlag == 1) {
		demo.InitialHttpClient();
		demo.SendHttpPack();
		iFlag = demo.RecvHttpPack();
		demo.CloseSocket();
	}
	return 0;
}








