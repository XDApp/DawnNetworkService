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
	char buf[1000];
	strncpy(buf, Data->Data, Data->Size);
	std::cout << buf << std::endl;
	Data->Size -= sizeof(Data->Size) + sizeof(Data->EncryptType);
	this->Service->DataLayer->Receive(Data);
}

void DNPacketLayer::Send(DNTransData *Data)
{
	char buf[1000];
	strncpy(buf, Data->Data, Data->Size);
	std::cout << buf << std::endl;
	Data->Size += sizeof(Data->Size) + sizeof(Data->EncryptType);
	this->Service->NetworkLayer->Send(Data);
}
