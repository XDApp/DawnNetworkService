#pragma once
#include "DNCmd.h"

class DNEventManager;
class DNCmdToken :
	public DNCmd
{
public:
	DNCmdToken(DNLayerService* service);
	~DNCmdToken();
	virtual void Send(DSocketAddrIn *Addr);
	virtual void Recv(DNTransData* Data);
};

class DNCmdTokenReply :
	public DNCmd
{
public:
	DNCmdTokenReply(DNLayerService* service);
	~DNCmdTokenReply();
	virtual void Send(DSocketAddrIn *Addr);
	virtual void Recv(DNTransData* Data);

	DNEventManager *WhenRecv;
};

