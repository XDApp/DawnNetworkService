#include "stdafx.h"
#include "DNUserLayer.h"
#include "DNLayerService.h"

DNUserLayer::DNUserLayer(DNLayerService *service) :DNLayer(service)
{
}


DNUserLayer::~DNUserLayer()
{
}

void DNUserLayer::Receive(DNTransData *Data)
{
	std::cout << Data->Data << std::endl;
}

void DNUserLayer::Send(DNTransData *Data)
{
	this->Service->CMDLayer->Send(Data);
}
