#include "stdafx.h"
#include "DDgramSocketI.h"


DDgramSocketI::DDgramSocketI() :DDgramSocket()
{
	int iMode = 1;
	ioctlsocket(this->sock, FIONBIO, (u_long FAR*) &iMode);
	int nRecvBufLen = 1024 * 1024;
	setsockopt(this->sock, SOL_SOCKET, SO_RCVBUF, (const char*)&nRecvBufLen, sizeof(int));
}


DDgramSocketI::~DDgramSocketI()
{
}
