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
	Data->Size -= sizeof(Data->Packet.Request.Cmd) + sizeof(Data->Packet.Request.ID);
	this->Service->UserLayer->Receive(Data);
}

void DNCmdLayer::Send(DNTransData *Data)
{
	Data->Size += sizeof(Data->Packet.Request.Cmd) + sizeof(Data->Packet.Request.ID);
	this->Service->DataLayer->Send(Data);
}
