#include "stdafx.h"
#include "DNCmd.h"
#include "DNLayer.h"
#include "DNUserLayer.h"
#include "DNLayerService.h"
#include "DSocketAddrIn.h"

DNCmd::DNCmd(DNLayerService* service) :Service(service)
{
}


DNCmd::~DNCmd()
{
}

void DNCmd::Send(DSocketAddrIn *Addr)
{

}

void DNCmd::Recv(DNTransData* Data)
{

}

DNTransData* DNCmd::CreatePacket()
{
	DNTransData *Data = new DNTransData;
	return Data;
}

void DNCmd::DestroyPacket(DNTransData *Data)
{
	delete Data->Addr;
	delete Data;
}