#include "stdafx.h"
#include "DNPacketLayer.h"
#include "DNLayerService.h"

DNPacketLayer::DNPacketLayer(DNLayerService *service) :DNLayer(service)
{
}


DNPacketLayer::~DNPacketLayer()
{
}

void DNPacketLayer::Receive(DNTransData *Data)
{
	this->Service->DataLayer->Receive(Data);
}

void DNPacketLayer::Send(DNTransData *Data)
{
	this->Service->NetworkLayer->Send(Data);
}
