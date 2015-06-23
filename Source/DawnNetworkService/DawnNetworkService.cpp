// DawnNetworkService.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "DNServiceManager.h"
#include "DNPacket.h"
#include "DSocketAddrIn.h"
#include "DNLayerService.h"
#include "DNLayer.h"
#include "DNUserLayer.h"
#include "DNCmdToken.h"
#include "DNCmdProcessor.h"
#include "DNCmdEcho.h"
#include "DNEventManager.h"
#include "DNEventHandler.h"

int main(int argc, char* argv[])
{
	bool Recved = false;
	DNServiceManager *Manager = new DNServiceManager();
	Manager->RunServ();

	auto TokenCmd = dynamic_cast<DNCmdToken*>(Manager->Service->Processor->GetCmd(DNCmdType::Token));
	auto EchoCmd = dynamic_cast<DNCmdEcho*>(Manager->Service->Processor->GetCmd(DNCmdType::Echo));
	auto REchoCmd = dynamic_cast<DNCmdEchoReply*>(Manager->Service->Processor->GetCmd(DNCmdType::ReplyEcho));
	
	auto Handler = new DNEventHandler([&Recved](DNTransData* Data)
	{
		Recved = true;
	});
	REchoCmd->WhenRecv->AddHandler(Handler);
	time_t Send = time(nullptr);

	EchoCmd->Send(new DSocketAddrIn("127.0.0.1", 8000));
	while (!Recved)Sleep(1);
	time_t Now = time(nullptr);
	std::cout << "RecvTime: " << Now - Send << std::endl;
	Sleep(10000);
	Manager->StopServ();

	system("PAUSE");
	return 0;
}

