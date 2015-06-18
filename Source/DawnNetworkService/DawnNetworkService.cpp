// DawnNetworkService.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "DSocketSystem.h"
#include "DSocket.h"
#include "DDgramSocket.h"
#include "DSocketAddrIn.h"
#include "DNPacket.h"

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
	/*

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

	std::thread ThreadSend(SendFunc);
	Socket->Bind(ListenAddr);
	std::thread ThreadRecv(RecvFunc);
	ThreadRecv.join();	
	ThreadSend.join();


*/

	DNPacket Packet;
	Packet.EncryptType = 0;
	Packet.Size = sizeof(DNRequest);
	Packet.Request.Cmd = 0;
	Packet.Request.ID = 0;
	strcpy(Packet.Request.Data, "Hello, World!");

	auto SendFunc = [Sender, Packet, ClientAddr]()
	{
		while (true)
		{
			Sender->Send((const char*)(&Packet), sizeof(Packet), ClientAddr);
			std::cout << "Data Sent!" << std::endl;
			Sleep(1000);
		}
	};
	auto RecvFunc = [Socket, TargetAddr]()
	{
		int len;
		DNPacket Packet;
		memset(&Packet, 0, sizeof(Packet));
		while (true)
		{
			len = Socket->Recv((char*)&Packet, sizeof(Packet), TargetAddr);
			
			if (len > 0)
			{
				std::cout << "Data Length: " << len << std::endl;
				std::cout << "RecvData from " << TargetAddr->GetAddress() << ":" << TargetAddr->GetPort() << std::endl;
				std::cout << "EncryptType: " << static_cast<int>(Packet.EncryptType) << std::endl;
				std::cout << "Size: " << static_cast<int>(Packet.Size) << std::endl;
				std::cout << "Command: " << static_cast<int>(Packet.Request.Cmd) << std::endl;
				std::cout << "ID: " << static_cast<int>(Packet.Request.ID) << std::endl;
				std::cout << "Data: " << Packet.Request.Data << std::endl;

			}
		}
	};
	
	std::thread ThreadSend(SendFunc);
	Socket->Bind(ListenAddr);
	std::thread ThreadRecv(RecvFunc);
	ThreadRecv.join();
	ThreadSend.join();

	Sleep(10000);



	delete Socket;
	delete Sender;
	std::cout << "Socket has been Destroyed successfully." << std::endl;
	DSocketSystem::Dispose();
	std::cout << "Socket System has been Disposed successfully." << std::endl;
	system("PAUSE");
	return 0;
}

