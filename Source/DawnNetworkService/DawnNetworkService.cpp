// DawnNetworkService.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "DSocketSystem.h"
#include "DSocket.h"
#include "DDgramSocket.h"
#include "DSocketAddrIn.h"

int main(int argc, char* argv[])
{
	DSocketSystem::Initialize();
	std::cout << "Socket System has been Initialized successfully." << std::endl;
	DSocketAddrIn *ListenAddr = new DSocketAddrIn(8000);
	DSocketAddrIn *ClientAddr = new DSocketAddrIn("127.0.0.1", 8000);
	DSocketAddrIn *TargetAddr = new DSocketAddrIn();
	DSocket *Socket = new DDgramSocket();
	DSocket *Sender = new DDgramSocket();
	std::cout << "Socket has been Created successfully." << std::endl;


	char* buf = "Hello, World!";
	
	
	auto SendFunc = [Sender, buf, ClientAddr]()
	{
		while (true)
		{
			Sender->Send(buf, strlen(buf), ClientAddr);
			std::cout << "Data Sent!" << std::endl;
			Sleep(1000);
		}
	};
	auto RecvFunc = [Socket, TargetAddr]()
	{
		char tmpStr[1000] = "";
		int len;
		while (true)
		{
			len = Socket->Recv(tmpStr, sizeof(tmpStr), TargetAddr);
			if (len > 0)
			{
				tmpStr[len] = '\0';
				std::cout << "RecvData from " << TargetAddr->GetAddress() << ":" << TargetAddr->GetPort() << std::endl;
				std::cout << tmpStr << std::endl;
			}
		}
	};

	if (argc > 1)
	{
		std::cout << "Client Mode" << std::endl;
		std::thread ThreadSend(SendFunc);
		ThreadSend.join();
	}
	else
	{
		std::cout << "Server Mode" << std::endl;
		Socket->Bind(ListenAddr);
		std::thread ThreadRecv(RecvFunc);
		ThreadRecv.join();	
	}
	

	Sleep(10000);

	delete Socket;
	delete Sender;
	std::cout << "Socket has been Destroyed successfully." << std::endl;
	DSocketSystem::Dispose();
	std::cout << "Socket System has been Disposed successfully." << std::endl;
	system("PAUSE");
	return 0;
}

