#pragma once
#include "stdafx.h"
#include <WINSOCK2.H>
#include <Windows.h>
#include <Tlhelp32.h>
#include <iostream>
#include <string> 
#pragma comment(lib,"ws2_32.lib")
#define HEAD_GET	"GET /sso/login.html?business=1 HTTP/1.1\r\n"
#define HOST		"Host: sso1.jszg.edu.cn\r\n"    
#define CONNECTION	"Connection: keep-alive\r\n"
#define CACHE		"Cache-Control: max-age=0\r\n"
#define UPGRADE		"Upgrade-Insecure-Requests: 1\r\n"
#define USER_AGENT	"User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.132 Safari/537.36\r\n"
#define REFER	   	"Referer:http://www.google.com/link?url=JuaNnrqwe-nH2nzDHKKeLtTTPfMaA_5K9lExtLnbkkpQlpWz1A-sAWjFf4wS22c_&wd=&eqid=cf4bfba30001b293000000065ddb4cd4\r\n"
#define ACCEPT		"Accept: text/html, */*; q=0.01\r\nAccept-Encoding: gzip, deflate\r\nAccept-Language: en-US,en;q=0.9\r\n"	
#define COOKIE		"Cookie: __guid=105251841.1513651351064468500.1574653161576.8662; monitor_count=1; Hm_lvt_f0d287187618f4bbbcf73fba0cd6b5b9=1574653162; Hm_lpvt_f0d287187618f4bbbcf73fba0cd6b5b9=1574653162; loginType=1\r\n"
#define CONTENT		"http://sso1.jszg.edu.cn/sso/login.html?business="
#define COMMAND		"1"

using namespace std;


/************************************************************************/
/*						THE CLASS: CHttpClient							*/
/************************************************************************/
class CHttpClient
{
	/*****************************/
	/*         PUBLIC			 */
	/*****************************/
public:
	/*****************************/
	/*    STRUCT: HttpRequest	 */
	/*****************************/
	/* The Structure which will be allocated for each User.
	 Request line:
		-sHead-------------------Used to indicate request method, request URI and requst version.
	 Request head:
		-sHostd to sModify-------Used to indicate additional information to be used by the server.
	 Request blank:
		-sBlank------------------A blank line after the request header is required.
	 Request data:
		-sContent----------------The body of the request data.
		-sCommand----------------As a signal which appends to the end of request data.
		-sRequest----------------It is the total of the above data, and needs to be send.
	*/
	struct SHttpRequest {
		string sHead = HEAD_GET;					
		string sHost;					//HOST;
		string sConnection = CONNECTION;
		string sCache = CACHE;
		string sUpgrade = UPGRADE;
		string sUserAgent = USER_AGENT;
		string sRefer = REFER;
		string sAccept = ACCEPT;
		string sCookie = COOKIE;
		string sBlank = "\r\n";
		string sContent;				// CONTENT;
		string sCommand = COMMAND;
		string sRequest;				//sHead + sHost + sConnection + sCache +
										//sUpgrade + sUserAgent + sRefer + sAccept +
										//sCookie + sBlank + sContent;
	};
	/* Initialize socket.
	 Aguments:
		-PRIVATE myNetTimeout----------Set the socket's timeout for sending and receving data pack.
	 Returns:
		-PRIVATE mySocket--------------Get a socket for sending and receiving date pack.
		-Flase-------------------------Initial socket failed.
		-True--------------------------Initial socket success.
	*/
	bool InitialHttpClient();
	/* Query message assembly and sending.
	 Aguments:
		-PRIVATE mySocket-----------A socket need to sending pack.
		-PRIVATE myPort-------------Tht port that send pack to server.
		-PRIVATE myServerIp---------The http server ip.
		-PRIVATE mySendDate---------Http packet need to send.
	 Returns:
		-Flase---------Sending http packet failed.
		-True----------Sending http packet success.
	*/
	bool SendHttpPack();
	/* Receive response message,get IP address or connection failed.
	 Aguments:
		-PRIVATE mySocket----------A socket need to receiving pack.
	 Returns:
		-1-----------Receive success and print the receive data then go on.
		-0-----------Receive success and print the receive data then end.
		--1----------Receive fail.
	*/
	int RecvHttpPack();
	/* Close the socket.
	 Aguments:
		-PRIVATE mySocket---------A pointer to close the http communication process.
	 Returns:
	*/
	void CloseSocket();
	/*  Initial http client parameters.
	 Arguments:
		-IN lpszCommand-----------Command that get information from server.
		-IN nNetTimeout-----------Set the socket's timeout for sending and receving data pack.
		-IN nPort-----------------Set tht port that send pack to server.
		-IN lpszServerIp----------Set the http server ip.
	 Returns:
		-PRIVATE myCommand
		-PRIVATEmyNetTimeout
		-PRIVATEmyPort
		-PRIVATEmyServerIP
		-PRIVATEmyRequest
	*/
	CHttpClient(IN const char *lpszCommand,
				IN int nNetTimeout,
				IN unsigned short nPort,
				IN const char* lpszServerIp);

	/*****************************/
	/*         PRIVATE			 */
	/*****************************/
private:
	/* Initial the following arguments in [InitialHttpClient].
	Arguments:
	-mySocket-----------------Socket for sending and receiving packets.
	-myClientRequest----------Structure used to generate http packets.
	-myPort-------------------Tht port that send pack to server.
	-myServerIp---------------The http server ip.
	-mySendDate---------------Http packet need to send.
	-myRequest----------------As the median of the fetch request of struct myClientRequest.request.
	-myNetTimeout-------------Set the packet sending and receiving delay.
	*/
	SOCKET mySocket;
	SHttpRequest myClientRequest;
	string myRequest;
	int myNetTimeout;
	unsigned short myPort;
	const char* myServerIp;
	const char * mySendData;
};

