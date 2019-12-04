#include "stdafx.h"
#include "http_server.h"
int main(int argc, const char *argv[]) {
	CHttpServer demo;
	demo.InitialHttpServer();
	while (true) {
		demo.RecieveHttpPacket();
		demo.SendHttpPacket();
	}
	demo.CloseHttpPacket();

	return 0;
}