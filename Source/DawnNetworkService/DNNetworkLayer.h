#pragma once
#include "DNLayer.h"
class DNNetworkLayer :
	public DNLayer
{
public:
	DNNetworkLayer(DNLayerService *service);
	~DNNetworkLayer();

	void Receive(DNTransData *Data);
	void Send(DNTransData *Data);
};

