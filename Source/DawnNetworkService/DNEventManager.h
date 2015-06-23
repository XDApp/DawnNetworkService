#pragma once

#include "DNPacket.h"

class DNEventHandler;
class DNEventManager
{
private:
	std::vector<DNEventHandler*>CallbackList;
public:
	DNEventManager();
	~DNEventManager();
	void Call(DNTransData* Data);
	void AddHandler(DNEventHandler *Callback);
	void RemoveHandler(DNEventHandler *Callback);
};

