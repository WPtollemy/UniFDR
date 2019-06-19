#include "stdafx.h"
#include "FDRClientNetwork.h"

//Constructor
FDRClientNetwork::FDRClientNetwork() {
	setup();
}

FDRClientNetwork::~FDRClientNetwork() {
	closesocket(s);
	WSACleanup();
}


//Other methods

void FDRClientNetwork::setup() {

	std::cout << "Attempting to initialise WinSock..." << std::endl;

	try {
		/* Initialise Winsock */
		if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
			throw std::runtime_error("Failed to initialise WinSock. Error code: " + WSAGetLastError());
		/* Create Socket */
		if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
			throw std::runtime_error("Failed to create socket. Error code: " + WSAGetLastError());
	}
	catch (std::runtime_error exception) {
		std::cerr << exception.what() << std::endl;
		exit(EXIT_FAILURE);	//Exit client
	}

	std::cout << "Socket initialised successfully." << std::endl;

	//setup address structure
	memset((char *)&in_addr_sock, 0, sizeof(in_addr_sock));
	in_addr_sock.sin_family = AF_INET;
	in_addr_sock.sin_port = htons(PORT);
	inet_pton(AF_INET, "127.0.0.1", &in_addr_sock.sin_addr);
}

void FDRClientNetwork::sendData(std::string str) {
	size_t sizeTemporary;// = toSend.length();

	sizeTemporary = str.length();
	//const char* charSend = toSend.c_str();

	//send general packet size
	if (sendto(s, (char*)&sizeTemporary, sizeof(int), 0, (struct sockaddr *)&in_addr_sock, sockLen) == SOCKET_ERROR) {
		printf("sendto() failed with error code : %d", WSAGetLastError());
	}

	//Send packet itself
	//if (sendto(s, message, strlen(message), 0, (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
	if (sendto(s, str.c_str(), sizeTemporary, 0, (struct sockaddr *)&in_addr_sock, sockLen) == SOCKET_ERROR)
	{
		printf("sendto() failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	std::cout << "Packet sent successfully" << std::endl;

	//receive a reply and print it
	//clear the buffer by filling null, it might have previously received data
	//memset(buf, '\0', BUFLEN);

	//puts(buf);
}