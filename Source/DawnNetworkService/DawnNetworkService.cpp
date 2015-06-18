// DawnNetworkService.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "DNServiceManager.h"
#include "DNPacket.h"
#include "DSocketAddrIn.h"
#include "DNLayerService.h"
#include "DNLayer.h"

int main(int argc, char* argv[])
{
	DNServiceManager *Manager = new DNServiceManager();
	Manager->RunServ();
	const char* buf = "Hello, World!";
	DNTransData* data = new DNTransData;
	data->Cmd = data->ID = data->Size = 0;
	data->Addr = new DSocketAddrIn("127.0.0.1", 8000);
	strcpy(data->Data, buf);
	for (int i = 0; i < 10; i++)
	{
		Manager->Service->UserLayer->Send(data);
	}
	Sleep(100000);
	Manager->StopServ();
	system("PAUSE");
	return 0;
}

