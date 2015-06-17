#include "stdafx.h"
#include "DSocketSystem.h"
#include "DSocketException.h"

DSocketSystem::DSocketSystem()
{
}


DSocketSystem::~DSocketSystem()
{
}

void DSocketSystem::Initialize()
{
	//TODO: Add Error handling system
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		DSocketSystem::Exception("WSA Startup Error");
	}
}

void DSocketSystem::Exception(const std::string& errorInfo)
{
	std::cerr << errorInfo;
	throw(new DSocketException(errorInfo));
}

void DSocketSystem::Dispose()
{
	WSACleanup();
}

WSADATA DSocketSystem::wsaData;