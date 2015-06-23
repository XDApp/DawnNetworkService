#pragma once

#include "DNPacket.h"
#include "DNLayerService.h"
#include "DNLayer.h"

class DSocketAddrIn;

enum class DNCmdType
{
	Echo = (DNCommand)0,
	ReplyEcho,
	Token,
	ReplyToken
};

class DNCmd
{
protected:
	DNLayerService* Service;
public:
	DNCmd(DNLayerService* service);
	~DNCmd();
	virtual void Send(DSocketAddrIn *Addr);
	virtual void Recv(DNTransData* Data);

	DNTransData* CreatePacket();
	void DestroyPacket(DNTransData *Data);
};

