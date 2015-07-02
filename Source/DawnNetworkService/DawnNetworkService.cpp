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

#include "DRSA.h"
#include "DResource.h"

#include "DConfig.h"

int main(int argc, char* argv[])
{
	/*
	DNServiceManager *Manager = new DNServiceManager();
	Manager->RunServ();

	DRSA::Randomize();
	auto key = DRSA::CreateKey(DRSA::GenerateRandString(), 1024);
	std::string CurrentPath = DResource::UnicodeToANSI(DResource::GetPath(nullptr)) + "\\";
	DRSA::SavePubKey(key, CurrentPath + "Public.DRSAKey");
	DRSA::SavePriKey(key, CurrentPath + "Private.DRSAKey", "123456");

	key = nullptr;

	key = DRSA::LoadPriKey(CurrentPath + "Private.DRSAKey", "123456");

	auto evp_key = DRSA::ToEVP(key);

	Manager->StopServ();
	*/


	DNServiceManager *Manager = new DNServiceManager();
	Manager->RunServ();
	DNUserLayer *userLayer = dynamic_cast<DNUserLayer*>(Manager->Service->UserLayer);

	DNCmdTokenReply* RTokenCmd = dynamic_cast<DNCmdTokenReply*>(Manager->Service->Processor->GetCmd(DNCmdType::ReplyToken));
	DNCmdToken* TokenCmd = dynamic_cast<DNCmdToken*>(Manager->Service->Processor->GetCmd(DNCmdType::Token));
	
	RTokenCmd->WhenRecv->AddHandler(new DNEventHandler([](DNTransData *Data){
		char tmp[30];
		strncpy_s(tmp, Data->Data, Data->Size);
		std::cout << tmp<<std::endl;
	}));
TokenCmd->Send(new DSocketAddrIn("192.168.0.105", 6000));
	while (true)
	{
		
		Sleep(1000);
	}
	Manager->StopServ();

	system("PAUSE");
	return 0;
}


/*
int main(int argc, char* argv[])
{
	int EchoCount;
	int SendCount;
	EchoCount = 0;
	SendCount = 0;
	int Echo = 0, Send = 0;
	DNServiceManager *Manager = new DNServiceManager();
	Manager->RunServ();
	DNUserLayer *userLayer = dynamic_cast<DNUserLayer*>(Manager->Service->UserLayer);

	std::cout << "Echo Sending Example" << std::endl;
	auto SendFunc = [&SendCount, &Manager, argv]()
	{
		std::cout << "Sending..." << std::endl;
		DNCmdEcho* cmd = dynamic_cast<DNCmdEcho*>(Manager->Service->Processor->GetCmd(DNCmdType::Echo));
		while (true)
		{
			SendCount++;
			cmd->Send(new DSocketAddrIn(argv[1], 8000));
		}
	};
	auto Handler = new DNEventHandler([&EchoCount](DNTransData* Data)
	{
		EchoCount++;
	});
	DNCmdEchoReply* REchoCmd = dynamic_cast<DNCmdEchoReply*>(Manager->Service->Processor->GetCmd(DNCmdType::ReplyEcho));
	REchoCmd->WhenRecv->AddHandler(Handler);
	std::thread *ThreadSend;

	if (argv[2] == "send")ThreadSend = new std::thread(SendFunc);

	int _EchoCount, _SendCount;
	time_t ori = time(nullptr);
	while (true)
	{
		_EchoCount = EchoCount;
		_SendCount = SendCount;
		Echo += _EchoCount;
		Send += _SendCount;
		EchoCount = SendCount = 0;
		Sleep(2000);
		std::cout << "Send " << Send << " Packets" << "\t\t";
		std::cout << "Recv " << Echo << " Packets" << std::endl;
		time_t now = time(nullptr);
		std::cout << "Recv " << Echo << " Packets in " << (now - ori) << " seconds" << std::endl;
		std::cout << "Loss: " << (float)Echo / Send << std::endl;
		ori = time(nullptr);
		Echo = Send = 0;
	}

	if (argv[2] == "send")
	{
		ThreadSend->detach();
		delete ThreadSend;
	}
	Manager->StopServ();
	system("PAUSE");
	return 0;
}


*/