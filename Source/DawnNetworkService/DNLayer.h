#pragma once

#include "DNPacket.h"

class DNLayer
{
public:
	DNLayer();
	~DNLayer();

	virtual void Receive(DNTransData *Data) = 0;
	virtual void Send(DNTransData *Data) = 0;

	DNTransData* CreatePacket();
	void DestroyPacket(DNTransData *Data);
};

