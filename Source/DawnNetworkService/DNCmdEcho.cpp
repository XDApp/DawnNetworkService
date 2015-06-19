#include "stdafx.h"
#include "DNCmdEcho.h"
#include "DNCmdProcessor.h"
#include "DNPacket.h"
#include "DSocketAddrIn.h"

DNCmdEcho::DNCmdEcho(DNLayerService* service) :DNCmd(service)
{
}

DNCmdEcho::~DNCmdEcho()
{
}

void DNCmdEcho::Send(DSocketAddrIn *Addr)
{
	DNTransData *Data = this->CreatePacket();
	Data->Addr = Addr;
	Data->Cmd = (DNCommand)DNCmdType::Echo;
	Data->Size = 0;
	this->Service->UserLayer->Send(Data);
}

void DNCmdEcho::Recv(DNTransData* Data)
{
	DNCmdEchoReply *Cmd = dynamic_cast<DNCmdEchoReply*>(this->Service->Processor->GetCmd(DNCmdType::ReplyEcho));
	Cmd->Send(Data->Addr->Clone());
}

DNCmdEchoReply::DNCmdEchoReply(DNLayerService* service) :DNCmd(service)
{
}


DNCmdEchoReply::~DNCmdEchoReply()
{
}
void DNCmdEchoReply::Send(DSocketAddrIn *Addr)
{
	DNTransData *Data = this->CreatePacket();
	Data->Addr = Addr;
	Data->Cmd = (DNCommand)DNCmdType::ReplyEcho;
	Data->Size = 0;
	this->Service->UserLayer->Send(Data);
}


extern int EchoCount;

void DNCmdEchoReply::Recv(DNTransData* Data)
{
	EchoCount++;
}
