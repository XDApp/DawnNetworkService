#include "stdafx.h"
#include "DNLayer.h"
#include "DNLayerService.h"
#include "DSocketAddrIn.h"

DNLayer::DNLayer(DNLayerService* service) :Service(service)
{
}


DNLayer::~DNLayer()
{
}

DNTransData* DNLayer::CreatePacket()
{
	DNTransData *Data = new DNTransData;
	return Data;
}

void DNLayer::DestroyPacket(DNTransData *Data)
{
	delete Data->Addr;
	delete Data;
}