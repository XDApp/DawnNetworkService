#include "stdafx.h"
#include "DNDataLayer.h"
#include "DNLayerService.h"
#include "DConfig.h"
#include "DNPacket.h"
#include "DRSA.h"

DNDataLayer::DNDataLayer(DNLayerService *service) :DNLayer(service)
{
}


DNDataLayer::~DNDataLayer()
{
}

void DNDataLayer::Receive(DNTransData *Data)
{
	DecryptData(Data);
	this->Service->CMDLayer->Receive(Data);
}

void DNDataLayer::Send(DNTransData *Data)
{
	EncryptData(Data);
	this->Service->PacketLayer->Send(Data);
}

void DNDataLayer::EncryptData(DNTransData *Data)
{
	char ori[DNPacketLength];
	strncpy_s(ori, Data->Data, Data->Size);
	DRSA::RSAEncrypt(this->Service->Config->PubKey, (unsigned char*)(ori), Data->Size, (unsigned char*)(Data->Data), Data->Size);
}

void DNDataLayer::DecryptData(DNTransData *Data)
{
	char ori[DNPacketLength];
	strncpy_s(ori, Data->Data, Data->Size);
	DRSA::RSADecrypt(this->Service->Config->PriKey, (unsigned char*)(ori), Data->Size, (unsigned char*)(Data->Data), Data->Size);
}


