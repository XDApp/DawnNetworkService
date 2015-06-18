#include "stdafx.h"
#include "DSocket.h"
#include "DSocketAddrIn.h"
#include "DSocketSystem.h"

DSocket::DSocket()
{
}
DSocket::~DSocket()
{

}

void DSocket::Send(const char* buf, int length, const DSocketAddrIn* addr)
{
	sendto(this->sock, buf, length, 0, addr->GetAddr(),addr->GetAddrSize());
}
int DSocket::Recv(char* buf, int length, DSocketAddrIn* addr)
{
	return recvfrom(this->sock, buf, length, 0, (sockaddr*)(&addr->sockAddr), &addr->AddrSize);
}
void DSocket::Bind(const DSocketAddrIn* addr)
{
	if (bind(this->sock, addr->GetAddr(), addr->GetAddrSize()) == SOCKET_ERROR)
	{
		DSocketSystem::Exception("Bind Error");
	}
}
