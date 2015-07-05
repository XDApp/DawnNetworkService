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
	//DecryptData(Data);
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
	int _oSize = Data->Size;
	Data->Size = DNRequestLength - 2;
	DRSA::RSAEncrypt(this->Service->Config->PubKey, (unsigned char*)(ori), _oSize, (unsigned char*)(Data->Data), Data->Size);
	DecryptData(Data);
}

void DNDataLayer::DecryptData(DNTransData *Data)
{
	char ori[DNPacketLength];
	strncpy_s(ori, Data->Data, Data->Size);
	int _oSize = Data->Size;
	Data->Size = DNRequestLength - 2;
	DRSA::RSADecrypt(this->Service->Config->PriKey, (unsigned char*)(ori), _oSize, (unsigned char*)(Data->Data), Data->Size);
}


