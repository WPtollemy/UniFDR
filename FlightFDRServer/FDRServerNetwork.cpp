#include "stdafx.h"
#include "FDRServerNetwork.h"
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <chrono>
#include <ctime>
#include "DataStorer.h"


FDRServerNetwork::FDRServerNetwork() {
	setup();
}


FDRServerNetwork::~FDRServerNetwork()
{
}


//Other methods
void FDRServerNetwork::setup() {

	try {
		if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
			throw std::runtime_error("Failed. Error Code:  " + WSAGetLastError());
		}
	}
	catch (std::runtime_error exception) {

		std::cerr << exception.what() << std::endl;
		exit(EXIT_FAILURE);
	}

	std::cout << "Initialised successfully." << std::endl;



	//Socket
	try {
		if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET) {
			throw std::runtime_error("Could not create socket:  " + WSAGetLastError());
		}

		std::cout << "Socket created successfully." << std::endl;
	}
	catch (std::runtime_error exception) {
		std::cerr << exception.what() << std::endl;
	}

	//Addr struct
	serv_sock.sin_family = AF_INET;
	serv_sock.sin_addr.s_addr = INADDR_ANY;
	serv_sock.sin_port = htons(PORT);


	//Bind
	try {
		if (bind(sock, (struct sockaddr *)&serv_sock, sizeof(serv_sock)) == SOCKET_ERROR) {
			throw std::runtime_error("Bind failed with error code:  " + WSAGetLastError());
		}
		std::cout << "Bind completed.";
	}
	catch (std::runtime_error exception) {
		std::cerr << exception.what() << std::endl;
	}
}

void FDRServerNetwork::startListening() {

	size_t sizeInc;

	while (true) {

		std::cout << "Waiting for data" << std::endl;

		//clear the buffer by filling null, it might have previously received data
		//memset(buffer, '\0', BUFLEN);

		//receive IncomingID
		if ((recv_len = recvfrom(sock, (char*)&sizeInc, sizeof(size_t), 0, (struct sockaddr *) &in_addr_sock, &slen)) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		std::cout << "Size:  " << std::to_string(sizeInc) << std::endl;
		const int size = sizeInc + 1;
		char* buffer = new char[sizeInc + 1]; //Cast received data to IncomingID struct
		buffer[sizeInc] = '\0';

		//Receive packet
		if ((recv_len = recvfrom(sock, buffer, sizeInc, 0, (struct sockaddr *) &in_addr_sock, &slen)) == SOCKET_ERROR) {
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		std::string receivedData(buffer);
		std::cout << "Packet recieved: " << receivedData << "  -  " + currentTime();
		deserialise(receivedData);
	}
}

void FDRServerNetwork::run() {
	std::thread t(&FDRServerNetwork::startListening, this);
	t.detach();
}

void FDRServerNetwork::deserialise(std::string str) {
	std::string	flightNumber;
	double fuelLevel;
	float speed;
	double pressureAltitude;
	float latitude;
	float longitude;

	std::stringstream sstr(str);

	sstr >> flightNumber;
	sstr >> fuelLevel;
	sstr >> speed;
	sstr >> pressureAltitude;
	sstr >> latitude;
	sstr >> longitude;

	tempPlane.setFlightNumber(flightNumber);
	tempPlane.setFuelLevel(fuelLevel);
	tempPlane.setSpeed(speed);
	tempPlane.setPressureAltitude(pressureAltitude);
	tempPlane.setLatitude(latitude);
	tempPlane.setLongitude(longitude);

	if (planesLinked.size() == 0)
		planesLinked.push_back(tempPlane);
	else {
		for (int i = 0; i < planesLinked.size(); i++) {
			if (planesLinked[i].getFlightNumber() == tempPlane.getFlightNumber()) {
				planesLinked[i] = tempPlane;
				planeToAdd = false;
				break;
			}
			else
				planeToAdd = true;
		}
	}

	if(planeToAdd)
		planesLinked.push_back(tempPlane);

	setTimes(tempPlane);

	DataStorer logger;
	logger.logData(tempPlane.getFlightNumber(), str + "  -  " + currentTime());
}

std::string FDRServerNetwork::currentTime(){
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);

	char str[26];
	ctime_s(str, sizeof str, &now_c);

	std::string temp(str);
	return str;
}

std::vector<Plane> FDRServerNetwork::refresh() {
	return this->planesLinked;
}

void FDRServerNetwork::setTimes(Plane tempPlane) {
	for (int i = 0; i < planesLinked.size(); i++) {
		if (planesLinked[i].getFlightNumber() == tempPlane.getFlightNumber())
			planesLinked[i].restartTime();
	}
}