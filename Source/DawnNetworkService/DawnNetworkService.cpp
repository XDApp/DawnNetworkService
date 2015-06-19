// DawnNetworkService.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "DNServiceManager.h"
#include "DNPacket.h"
#include "DSocketAddrIn.h"
#include "DNLayerService.h"
#include "DNLayer.h"
#include "DNUserLayer.h"

int EchoCount;
int SendCount;

int main(int argc, char* argv[])
{
	const int EchoSum = 100000;
	EchoCount = 0;
	SendCount = 0;
	DNServiceManager *Manager = new DNServiceManager();
	Manager->RunServ();
	DNUserLayer *userLayer = dynamic_cast<DNUserLayer*>(Manager->Service->UserLayer);

	time_t Time = time(nullptr);
	for (int i = 0; i < EchoSum; i++)
	{
		userLayer->Send_Cmd_Echo(new DSocketAddrIn("127.0.0.1", 8000));
	}
	time_t TimeSec = time(nullptr);
	std::cout << "Count: " << SendCount << std::endl;
	std::cout << "Send Complete in " << TimeSec - Time << std::endl;
	while (EchoCount < EchoSum)Sleep(100);std::cout << "Recv Complete." << std::endl;
	Manager->StopServ();
	system("PAUSE");
	return 0;
}

