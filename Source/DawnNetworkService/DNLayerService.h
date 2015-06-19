#pragma once

class DSocket;
class DNLayer;
class DNCmdProcessor;

class DNLayerService
{
public:
	DNLayerService();
	~DNLayerService();
	DNLayer *NetworkLayer;
	DNLayer *PacketLayer;
	DNLayer *DataLayer;
	DNLayer *CMDLayer;
	DNLayer *UserLayer;

	DSocket *ListenSocket;
	std::mutex SocketLock;

	DNCmdProcessor *Processor;
};

