#pragma once
class DSocketAddrIn
{
private:
	sockaddr_in sockAddr;
	int AddrSize;
public:
	friend class DSocket;
	DSocketAddrIn();
	DSocketAddrIn(int port);
	DSocketAddrIn(const char* addr, int port);
	~DSocketAddrIn();
	const sockaddr* GetAddr() const;
	const int GetAddrSize() const;
	const std::string GetAddress() const; 
	const int DSocketAddrIn::GetPort() const;
	DSocketAddrIn* Clone()const;
};
