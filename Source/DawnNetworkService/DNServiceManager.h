#pragma once

class DSocketAddrIn;
class DDgramSocket;
class DNLayerService;
class DConfig;

class DNServiceManager
{
public:
	DNLayerService *Service;
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

	void RegisterCommands();

	DConfig* config;
};

