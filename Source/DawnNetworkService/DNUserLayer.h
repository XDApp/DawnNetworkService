#pragma once
#include "DNLayer.h"

class DNCmdProcessor;

class DNUserLayer :
	public DNLayer
{
private:
public:
	DNUserLayer(DNLayerService *service);
	~DNUserLayer();

	void Receive(DNTransData *Data);
	void Send(DNTransData *Data); 

	void DNUserLayer::ProcessRecvCmd(DNTransData *Data);
};

