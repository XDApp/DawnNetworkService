#pragma once
#include "DNCmd.h"
class DNCmdEcho :
	public DNCmd
{
public:
	DNCmdEcho(DNLayerService* service);
	~DNCmdEcho();
	virtual void Send(DSocketAddrIn *Addr);
	virtual void Recv(DNTransData* Data);
};

class DNCmdEchoReply :
	public DNCmd
{
public:
	DNCmdEchoReply(DNLayerService* service);
	~DNCmdEchoReply();
	virtual void Send(DSocketAddrIn *Addr);
	virtual void Recv(DNTransData* Data);
};

