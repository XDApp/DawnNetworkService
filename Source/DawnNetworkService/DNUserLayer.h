#pragma once
#include "DNLayer.h"

enum class DNCmdType
{
	Echo = (DNCommand)0,
	ReplyEcho
};

class DNUserLayer :
	public DNLayer
{
public:
	DNUserLayer(DNLayerService *service);
	~DNUserLayer();

	void Receive(DNTransData *Data);
	void Send(DNTransData *Data); 

	void DNUserLayer::Send_Cmd_ReplyEcho(DSocketAddrIn *Addr);
	void DNUserLayer::Recv_Cmd_ReplyEcho(DNTransData *Data);
	void DNUserLayer::Send_Cmd_Echo(DSocketAddrIn *Addr);
	void DNUserLayer::Recv_Cmd_Echo(DNTransData *Data);

	void DNUserLayer::ProcessRecvCmd(DNTransData *Data);
};

