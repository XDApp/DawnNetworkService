#pragma once

typedef unsigned short DNPacketSize;
typedef unsigned char DNEncryptType;
typedef unsigned char DNCommand;
typedef unsigned char DNMessageID;
typedef char DNData;
const unsigned int DNPacketLength = 1300;
const unsigned int DNRequestLength = 1290;
#pragma pack(push, 1)

class DSocketAddrIn;

struct DNRequest
{
	DNCommand Cmd;
	DNMessageID ID;
	DNData Data[DNRequestLength - 2];
};

struct DNPacket
{
	DNPacketSize Size;
	DNEncryptType EncryptType;
	DNRequest Request;
};
#pragma pack(pop)

struct DNTransData
{
	DNPacket Packet;

	DNPacketSize &Size = Packet.Size;
	DNEncryptType &EncryptType = Packet.EncryptType;

	DNCommand &Cmd = Packet.Request.Cmd;
	DNMessageID &ID = Packet.Request.ID;
	DNData *Data = Packet.Request.Data;

	DSocketAddrIn* Addr;
};