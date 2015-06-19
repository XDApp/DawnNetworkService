// DawnNetworkService.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "DNServiceManager.h"
#include "DNPacket.h"
#include "DSocketAddrIn.h"
#include "DNLayerService.h"
#include "DNLayer.h"
#include "DNUserLayer.h"
#include "DNCmdEcho.h"
#include "DNCmdProcessor.h"

int EchoCount;
int SendCount;

int main(int argc, char* argv[])
{
	const int PacketToRecv = 10000;
	EchoCount = 0;
	SendCount = 0;
	int Echo = 0, Send = 0;
	DNServiceManager *Manager = new DNServiceManager();
	Manager->RunServ();
	DNUserLayer *userLayer = dynamic_cast<DNUserLayer*>(Manager->Service->UserLayer);

	std::cout << "Echo Sending Example" << std::endl;
	auto SendFunc = [&Manager]()
	{
		std::cout << "Sending..." << std::endl;
		DNCmdEcho* cmd = dynamic_cast<DNCmdEcho*>(Manager->Service->Processor->GetCmd(DNCmdType::Echo));
		while (true)
		{
			SendCount++;
			cmd->Send(new DSocketAddrIn("192.168.0.101", 8000));
			Sleep(1);
		}
	};
	std::thread ThreadSend(SendFunc);
	int _EchoCount, _SendCount;
	time_t ori = time(nullptr);
	while (true)
	{
		_EchoCount = EchoCount;
		_SendCount = SendCount;
		Echo += _EchoCount;
		Send += _SendCount;
		EchoCount = SendCount = 0;
		Sleep(1000);
		std::cout << "Send " << Send << " Packets" << "\t\t";
		std::cout << "Recv " << Echo << " Packets" << std::endl;
		if (Echo >= PacketToRecv)
		{
			time_t now = time(nullptr);
			std::cout << "Recv " << Echo << " Packets in " << (now - ori) << " seconds" << std::endl;
			std::cout << "Loss: " << (float)Echo / Send << std::endl;
			ori = time(nullptr);
			Echo = Send = 0;
		}
	}
	
	ThreadSend.detach();
	Manager->StopServ();
	system("PAUSE");
	return 0;
}

