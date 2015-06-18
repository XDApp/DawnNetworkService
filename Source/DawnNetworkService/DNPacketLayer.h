#pragma once
#include "DNLayer.h"
class DNPacketLayer :
	public DNLayer
{
public:
	DNPacketLayer(DNLayerService *service);
	~DNPacketLayer();

	void Receive(DNTransData *Data);
	void Send(DNTransData *Data);
};

