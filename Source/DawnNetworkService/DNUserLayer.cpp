#include "stdafx.h"
#include "DNUserLayer.h"
#include "DNLayerService.h"
#include "DNPacket.h"
#include "DSocketAddrIn.h"

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

extern int EchoCount;

void DNUserLayer::Recv_Cmd_ReplyEcho(DNTransData *Data)
{
	EchoCount++;
}

void DNUserLayer::Send_Cmd_ReplyEcho(DSocketAddrIn *Addr)
{
	DNTransData *Data = this->CreatePacket();
	Data->Addr = Addr;
	Data->Cmd = (DNCommand)DNCmdType::ReplyEcho;
	Data->Size = 0;
	this->Send(Data);
}

void DNUserLayer::Recv_Cmd_Echo(DNTransData *Data)
{
	this->Send_Cmd_ReplyEcho(Data->Addr->Clone());
}

void DNUserLayer::Send_Cmd_Echo(DSocketAddrIn *Addr)
{
	DNTransData *Data = this->CreatePacket();
	Data->Addr = Addr;
	Data->Cmd = (DNCommand)DNCmdType::Echo;
	Data->Size = 0;
	this->Send(Data);
}

void DNUserLayer::ProcessRecvCmd(DNTransData *Data)
{
	DNCommand Cmd = Data->Packet.Request.Cmd;
	if (Cmd == (DNCommand)DNCmdType::Echo)
	{
		this->Recv_Cmd_Echo(Data);
	}
	if (Cmd == (DNCommand)DNCmdType::ReplyEcho)
	{
		this->Recv_Cmd_ReplyEcho(Data);
	}
}