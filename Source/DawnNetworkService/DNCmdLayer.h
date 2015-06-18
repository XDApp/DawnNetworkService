#pragma once
#include "DNLayer.h"
class DNCmdLayer :
	public DNLayer
{
public:
	DNCmdLayer(DNLayerService *service);
	~DNCmdLayer();

	void Receive(DNTransData *Data);
	void Send(DNTransData *Data);
};

