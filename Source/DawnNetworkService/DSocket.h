#pragma once

class DSocketAddrIn;

class DSocket
{
protected:
	SOCKET sock;
public:
	DSocket();
	virtual ~DSocket();
	void Send(const char* buf, int length, const DSocketAddrIn* addr);
	int Recv(char* buf, int length, DSocketAddrIn* addr);
	void Bind(const DSocketAddrIn* addr);
};

