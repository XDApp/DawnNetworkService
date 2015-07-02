#pragma once

typedef size_t DNPacketSize;
typedef unsigned char DNCommand;
typedef unsigned char DNMessageID;
typedef char DNData;

enum class DNEncryptType : unsigned char
{
	None = 0,
	RSA = 1, Sync = 2, Unknown = 3
};

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
	DNPacket Packet;										//Network Layer Packet

	DNPacketSize &Size = Packet.Size;						//User Layer Size
	DNEncryptType &EncryptType = Packet.EncryptType;		//User Layer EncryptType

	DNCommand &Cmd = Packet.Request.Cmd;					//User Layer Command
	DNMessageID &ID = Packet.Request.ID;					//Packet Layer ID
	DNData *Data = Packet.Request.Data;						//User Layer Data

	DSocketAddrIn* Addr;									//User Layer IP Address
};