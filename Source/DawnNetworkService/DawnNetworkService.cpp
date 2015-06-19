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
	const int EchoSum = 200000;
	EchoCount = 0;
	SendCount = 0;
	DNServiceManager *Manager = new DNServiceManager();
	Manager->RunServ();
	DNUserLayer *userLayer = dynamic_cast<DNUserLayer*>(Manager->Service->UserLayer);

	std::cout << "Echo Sending Example" << std::endl;
	while (true)
	{
		EchoCount = 0;
		std::cout << "Sending..." << std::endl;
		time_t Time = time(nullptr);
		DNCmdEcho* cmd = dynamic_cast<DNCmdEcho*>(Manager->Service->Processor->GetCmd(DNCmdType::Echo));
		for (int i = 0; i < EchoSum; i++)
		{
			cmd->Send(new DSocketAddrIn("127.0.0.1", 8000));
		}
		time_t TimeSec = time(nullptr);
		std::cout << "Count: " << SendCount << std::endl;
		std::cout << "Send Complete in " << TimeSec - Time << " secs" << std::endl;
		while (EchoCount < EchoSum)
		{
			std::cout << "Reply Recv: " << EchoCount << "/" << EchoSum << std::endl;
			Sleep(80);
		}
		std::cout << "Recv Complete." << std::endl;
		Sleep(10000);
	}
	Manager->StopServ();
	system("PAUSE");
	return 0;
}

