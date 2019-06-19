#pragma once

#include <WinSock2.h>
#include <WS2tcpip.h>	//For inet_pton
#pragma comment(lib, "Ws2_32.lib")
#include <string>
#include <iostream>
#define SERVER_IP 127.0.0.1
#define PORT 7274

class FDRClientNetwork {

	private:
		//Winsock variables
		struct sockaddr_in in_addr_sock;
		int s, sockLen = sizeof(in_addr_sock);
		WSADATA wsa;

	private:
		void setup();
		//void startTransmission();
		
	public:
		FDRClientNetwork();	/* Constructor */
		~FDRClientNetwork(); /* Destructor */
		void sendData(std::string str);
};