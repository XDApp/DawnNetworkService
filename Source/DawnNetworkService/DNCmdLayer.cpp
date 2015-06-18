#include "stdafx.h"
#include "DNCmdLayer.h"
#include "DNLayerService.h"

DNCmdLayer::DNCmdLayer(DNLayerService *service) :DNLayer(service)
{
}


DNCmdLayer::~DNCmdLayer()
{
}

void DNCmdLayer::Receive(DNTransData *Data)
{
	this->Service->UserLayer->Receive(Data);
}

void DNCmdLayer::Send(DNTransData *Data)
{
	this->Service->DataLayer->Send(Data);
}
