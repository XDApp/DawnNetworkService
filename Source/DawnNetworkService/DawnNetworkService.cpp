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

	Manager->StopServ();

	system("PAUSE");
	return 0;
}

