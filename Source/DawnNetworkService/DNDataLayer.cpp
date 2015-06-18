#include "stdafx.h"
#include "DNDataLayer.h"
#include "DNLayerService.h"

DNDataLayer::DNDataLayer(DNLayerService *service) :DNLayer(service)
{
}


DNDataLayer::~DNDataLayer()
{
}

void DNDataLayer::Receive(DNTransData *Data)
{
	this->Service->CMDLayer->Receive(Data);
}

void DNDataLayer::Send(DNTransData *Data)
{
	this->Service->PacketLayer->Send(Data);
}
