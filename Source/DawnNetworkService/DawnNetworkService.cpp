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

int main(int argc, char* argv[])
{
	bool Recved = false;
	DNServiceManager *Manager = new DNServiceManager();
	Manager->RunServ();

	DRSA::Randomize();
	auto key = DRSA::CreateKey(DRSA::GenerateRandString(), 1024);
	DRSA::SavePubKey(key, "Public.DRSAKey");
	DRSA::SavePriKey(key, "Private.DRSAKey", "123456");

	Manager->StopServ();

	system("PAUSE");
	return 0;
}

