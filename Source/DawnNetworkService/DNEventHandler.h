#pragma once

#include "DNPacket.h"

typedef std::function<void(DNTransData*)> DNEventCallback;
class DNEventHandler
{
private:
	DNEventCallback Callback;
public:
	DNEventHandler(DNEventCallback callback);
	~DNEventHandler();

	void Run(DNTransData *Data);
};

