#pragma once
#include "DNLayer.h"
class DNDataLayer :
	public DNLayer
{
public:
	DNDataLayer(DNLayerService *service);
	~DNDataLayer();

	void Receive(DNTransData *Data);
	void Send(DNTransData *Data);
};

