#pragma once

#include "DNPacket.h"

class DNLayerService;
class DNLayer
{
protected:
	DNLayerService *Service;
public:
	DNLayer(DNLayerService *service);
	~DNLayer();

	virtual void Receive(DNTransData *Data) = 0;
	virtual void Send(DNTransData *Data) = 0;

	DNTransData* CreatePacket();
	void DestroyPacket(DNTransData *Data);
};

