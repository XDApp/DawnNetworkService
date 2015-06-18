#pragma once
#include "DNLayer.h"
class DNUserLayer :
	public DNLayer
{
public:
	DNUserLayer(DNLayerService *service);
	~DNUserLayer();

	void Receive(DNTransData *Data);
	void Send(DNTransData *Data);
};

