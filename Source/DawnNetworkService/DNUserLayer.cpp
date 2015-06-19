#include "stdafx.h"
#include "DNUserLayer.h"
#include "DNLayerService.h"
#include "DNPacket.h"
#include "DSocketAddrIn.h"
#include "DNCmd.h"
#include "DNCmdProcessor.h"

DNUserLayer::DNUserLayer(DNLayerService *service) :DNLayer(service)
{
}


DNUserLayer::~DNUserLayer()
{
}

void DNUserLayer::Receive(DNTransData *Data)
{
	this->ProcessRecvCmd(Data);
	this->DestroyPacket(Data);
}

void DNUserLayer::Send(DNTransData *Data)
{
	this->Service->CMDLayer->Send(Data);
}

void DNUserLayer::ProcessRecvCmd(DNTransData *Data)
{
	DNCommand Cmd = Data->Packet.Request.Cmd;
	DNCmd *Command = this->Service->Processor->GetCmd((DNCmdType)Cmd);
	Command->Recv(Data);
}
