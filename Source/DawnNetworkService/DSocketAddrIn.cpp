#include "stdafx.h"
#include "DSocketAddrIn.h"

DSocketAddrIn::DSocketAddrIn()
{
	this->AddrSize = sizeof(this->sockAddr);
}

DSocketAddrIn::DSocketAddrIn(int port) 
{
	this->sockAddr.sin_family = AF_INET;
	this->sockAddr.sin_port = htons(port);
	this->sockAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	this->AddrSize = sizeof(this->sockAddr);
}

DSocketAddrIn::DSocketAddrIn(const char* addr, int port) : AddrSize(sizeof(sockaddr_in))
{
	this->sockAddr.sin_family = AF_INET;
	this->sockAddr.sin_port = htons(port);
	this->sockAddr.sin_addr.S_un.S_addr = inet_addr(addr);
	this->AddrSize = sizeof(this->sockAddr);
}

DSocketAddrIn::~DSocketAddrIn()
{
}

const sockaddr* DSocketAddrIn::GetAddr() const
{
	return (sockaddr*)&this->sockAddr;
}

const int DSocketAddrIn::GetAddrSize() const
{
	return this->AddrSize;
}

const std::string DSocketAddrIn::GetAddress() const
{
	return std::string(inet_ntoa(this->sockAddr.sin_addr));
}

const int DSocketAddrIn::GetPort() const
{
	return this->sockAddr.sin_port;
}

DSocketAddrIn* DSocketAddrIn::Clone() const
{
	DSocketAddrIn* Addr = new DSocketAddrIn();
	Addr->AddrSize = this->AddrSize;
	Addr->sockAddr = this->sockAddr;
	return Addr;
}