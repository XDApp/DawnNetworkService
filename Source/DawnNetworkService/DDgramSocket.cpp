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
	int iMode = 1;
	ioctlsocket(this->sock, FIONBIO, (u_long FAR*) &iMode);
}


DDgramSocket::~DDgramSocket()
{
	closesocket(this->sock);
}
