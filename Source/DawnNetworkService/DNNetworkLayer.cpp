#include "stdafx.h"
#include "DNNetworkLayer.h"
#include "DNLayerService.h"
#include "DSocket.h"

DNNetworkLayer::DNNetworkLayer(DNLayerService *service) :DNLayer(service)
{
}


DNNetworkLayer::~DNNetworkLayer()
{
}

void DNNetworkLayer::Receive(DNTransData *Data)
{
	this->Service->PacketLayer->Receive(Data);
}

void DNNetworkLayer::Send(DNTransData *Data)
{
	this->Service->ListenSocket->Send((const char*)(&Data->Packet), sizeof(Data->Packet), Data->Addr);
	this->DestroyPacket(Data);
}
