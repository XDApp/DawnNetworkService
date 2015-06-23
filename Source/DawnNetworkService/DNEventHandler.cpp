#include "stdafx.h"
#include "DNEventHandler.h"


DNEventHandler::DNEventHandler(DNEventCallback callback)
	:Callback(callback)
{
}


DNEventHandler::~DNEventHandler()
{
}

void DNEventHandler::Run(DNTransData *Data)
{
	this->Callback(Data);
}