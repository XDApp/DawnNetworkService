#include "stdafx.h"
#include "DDgramSocket.h"
#include "DSocketSystem.h"

DDgramSocket::DDgramSocket()
{
	//Todo: Add Error Handling
	this->sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (this->sock == INVALID_SOCKET)
	{
		DSocketSystem::Exception("Invalid Socket!");
	}
}


DDgramSocket::~DDgramSocket()
{
	closesocket(this->sock);
}
