#include "stdafx.h"
#include "DNServiceManager.h"
#include "DNLayerService.h"

#include "DConfig.h"
#include "DNNetworkLayer.h"
#include "DNDataLayer.h"
#include "DNPacketLayer.h"
#include "DNCmdLayer.h"
#include "DNUserLayer.h"
#include "DSocketSystem.h"

#include "DDgramSocket.h"
#include "DDgramSocketI.h"
#include "DSocketAddrIn.h"
#include "DSocketException.h"
#include "DNCmdProcessor.h"
#include "DNCmdEcho.h"
#include "DNCmdToken.h"

DNServiceManager::DNServiceManager()
{
}


DNServiceManager::~DNServiceManager()
{
}

void DNServiceManager::RegisterCommands()
{
	this->Service->Processor->Register(DNCmdType::Echo, new DNCmdEcho(this->Service));
	this->Service->Processor->Register(DNCmdType::ReplyEcho, new DNCmdEchoReply(this->Service));
	this->Service->Processor->Register(DNCmdType::Token, new DNCmdToken(this->Service));
	this->Service->Processor->Register(DNCmdType::ReplyToken, new DNCmdTokenReply(this->Service));
}

void DNServiceManager::RunServ()
{
	config = new DConfig();
	config->Generate();
	config->Load();

	this->Service = new DNLayerService;

	DNNetworkLayer *networkLayer = new DNNetworkLayer(DNServiceManager::Service);
	DNDataLayer *dataLayer = new DNDataLayer(DNServiceManager::Service);
	DNPacketLayer *packetLayer = new DNPacketLayer(DNServiceManager::Service);
	DNCmdLayer *cmdLayer = new DNCmdLayer(DNServiceManager::Service);
	DNUserLayer *userLayer = new DNUserLayer(DNServiceManager::Service);

	this->Service->NetworkLayer = networkLayer;
	this->Service->DataLayer = dataLayer;
	this->Service->PacketLayer = packetLayer;
	this->Service->CMDLayer = cmdLayer;
	this->Service->UserLayer = userLayer;

	this->Service->Processor = new DNCmdProcessor();
	this->RegisterCommands();

	this->Service->Config = config;

	DSocketSystem::Initialize();

	std::cout << "[Log] Dawn Network Service Initialized" << std::endl;

	this->RunSocket();
}

void DNServiceManager::StopServ()
{
	this->StopSocket();
	DSocketSystem::Dispose();

	delete this->Service->Processor;

	delete this->Service->NetworkLayer;
	delete this->Service->DataLayer;
	delete this->Service->PacketLayer;
	delete this->Service->CMDLayer;
	delete this->Service->UserLayer;

	delete this->Service->Config;
	std::cout << "[Log] Dawn Network Service Disposed" << std::endl;
}

void DNServiceManager::RunSocket()
{
	this->Service->ListenSocket = new DDgramSocketI();
	this->ListenAddr = new DSocketAddrIn(6000);
	this->Service->ListenSocket->Bind(this->ListenAddr);
	std::cout << "[Log] Socket Initialized" << std::endl;
	this->Receiving = true;
	auto RecvFunc = [this]()
	{
		int len;
		DNPacket Packet;
		DSocketAddrIn *AddrIn = new DSocketAddrIn();
		memset(&Packet, 0, sizeof(Packet));

		while (this->Receiving)
		{
			//while (!this->Service->SocketLock.try_lock())Sleep(10);
			len = this->Service->ListenSocket->Recv((char*)&Packet, sizeof(Packet), AddrIn);
			//this->Service->SocketLock.unlock();
			if (len > 0)
			{
				DNTransData *TransData = new DNTransData;
				TransData->Addr = AddrIn->Clone();
				TransData->Packet = Packet;
				this->Service->NetworkLayer->Receive(TransData);
			}
			if (len <= 0)
			{
				Sleep(500);
			}
		}
		this->ThreadDisposed = true;
		return;
	};
	this->ListenThread = new std::thread(RecvFunc);
	std::cout << "[Log] Socket Receiving" << std::endl;
}

void DNServiceManager::StopSocket()
{
	std::cout << "[Log] Socket Disposing" << std::endl;
	this->Receiving = false;
	this->ThreadDisposed = false;
	while (this->ThreadDisposed);
	this->ListenThread->detach();
	delete this->Service->ListenSocket;
	delete this->ListenThread;
	delete this->ListenAddr;
	std::cout << "[Log] Socket Disposed" << std::endl;
}