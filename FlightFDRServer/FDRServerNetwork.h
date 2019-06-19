#pragma once
#include <string>
#include <ctime>
#include "Plane.h"

#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib") //Winsock Library
#include <Ws2tcpip.h>
#define PORT 7274

class FDRServerNetwork
{
	private:
		//Winsock variables
		SOCKET sock;
		struct sockaddr_in serv_sock, in_addr_sock;
		int slen = sizeof(in_addr_sock), recv_len;
		//char buf[BUFLEN];
		WSADATA wsa;

		//Methods
		void setup();
		void startListening();

		void deserialise(std::string str);
		std::string currentTime();
		void setTimes(Plane);

		Plane tempPlane;
		std::vector<Plane> planesLinked;
		bool planeToAdd = false;

	public:
		FDRServerNetwork(); /* Constructor */
		~FDRServerNetwork(); /* Destructor */
		void run();
		std::vector<Plane> refresh();
};

