#include "stdafx.h"
#include "DStreamSocket.h"


DStreamSocket::DStreamSocket()
{
	this->sock = socket(AF_INET, SOCK_STREAM, 0);
}


DStreamSocket::~DStreamSocket()
{
	closesocket(this->sock);
}
