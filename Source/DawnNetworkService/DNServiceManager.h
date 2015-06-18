#pragma once

class DSocketAddrIn;
class DDgramSocket;
class DNLayerService;
class DNServiceManager
{
public:
	DNLayerService *Service;
	DDgramSocket *Socket;
	bool Receiving;
	bool ThreadDisposed;
private:
	DSocketAddrIn *ListenAddr;
	std::thread *ListenThread;
public:
	DNServiceManager();
	~DNServiceManager();

	void RunServ();
	void StopServ();
private:
	void RunSocket();
	void StopSocket();
};

