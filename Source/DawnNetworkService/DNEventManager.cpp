#include "stdafx.h"
#include "DNEventManager.h"
#include "DNEventHandler.h"

DNEventManager::DNEventManager()
{
}


DNEventManager::~DNEventManager()
{
}

void DNEventManager::Call(DNTransData* Data)
{
	for (DNEventHandler* Callback : this->CallbackList)
	{
		Callback->Run(Data);
	}
}
void DNEventManager::AddHandler(DNEventHandler *Callback)
{
	this->CallbackList.push_back(Callback);
}

void DNEventManager::RemoveHandler(DNEventHandler *Callback)
{
	this->CallbackList.erase(std::find(this->CallbackList.begin(), this->CallbackList.end(), Callback));
}