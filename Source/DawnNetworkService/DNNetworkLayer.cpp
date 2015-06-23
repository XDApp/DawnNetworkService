#include "stdafx.h"
#include "DNNetworkLayer.h"
#include "DNLayerService.h"
#include "DSocket.h"
#include "DNUserLayer.h"
#include "DNPacket.h"
#include "DNCmd.h"

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
	//while (!this->Service->SocketLock.try_lock())Sleep(50);
	this->Service->ListenSocket->Send((const char*)(&Data->Packet), Data->Size, Data->Addr);
	//this->Service->SocketLock.unlock();
	this->DestroyPacket(Data);
}
