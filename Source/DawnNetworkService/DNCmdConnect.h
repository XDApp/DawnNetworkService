#pragma once
#include "DNCmd.h"

class DNLayerService;

class DNCmdConnect :
	public DNCmd
{
public:
	DNCmdConnect(DNLayerService* service);
	~DNCmdConnect();
	virtual void Send(DSocketAddrIn *Addr) = 0;
	virtual void Recv(DNTransData* Data) = 0;
};

class DNCmdConnectReply :
	public DNCmd
{
public:
	DNCmdConnectReply(DNLayerService* service);
	~DNCmdConnectReply();
	virtual void Send(DSocketAddrIn *Addr) = 0;
	virtual void Recv(DNTransData* Data) = 0;
};
