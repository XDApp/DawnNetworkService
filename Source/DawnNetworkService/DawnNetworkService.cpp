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
	EVP_PKEY *pkey;
	pkey = EVP_PKEY_new();
	RSA *rsa;
	rsa = RSA_generate_key(1024, RSA_F4, nullptr, nullptr);
	EVP_PKEY_assign_RSA(pkey, rsa);

	Manager->StopServ();

	system("PAUSE");
	return 0;
}

